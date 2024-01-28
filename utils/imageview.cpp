#include "imageview.h"

ImageView::ImageView(QWidget *parent)
    :QWidget(parent)
{

    this->mState = STATE::loading;
    this->mStyle = STYLE::percentage;
    //Каталог кэша по умолчанию по текущему пути
    this->cacheDir = QDir::currentPath()+QDir::separator()+"cache";
    QDir dir(this->cacheDir);//Определяем, существует ли путь к кэшу
    if(!dir.exists()){
        dir.mkdir(this->cacheDir);
    }
    this->mManager = new QNetworkAccessManager(this);
    connect(this->mManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoad(QNetworkReply*)));

}
void ImageView::slotReplyPixmapLoad(QNetworkReply* reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        //Получаем данные изображения
        QByteArray bytes =  reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(bytes);
        this->setSucceedPixmap(pixmap);
        //Используем путь для генерации md5
        QString md5;
        QByteArray bb = QCryptographicHash::hash ( this->mUrl.toUtf8(), QCryptographicHash::Md5 );
        md5.append(bb.toHex());
        //запись в кэш
        QFile file(this->cacheDir+QDir::separator() + md5);
        if(!file.exists()){
            file.open(QIODevice::WriteOnly);
            file.close();
        }
        if (file.open(QIODevice::Append)){
            file.write(bytes);
        }
        file.close();
    }else{
        this->mState = STATE::failed;
        repaint();
    }
    this->mManager->deleteLater();

}
void ImageView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    if(this->mState == STATE::succeed){//Загрузка прошла успешно
        if(mStyle == STYLE::cover){
            //Динамический расчет длинной стороны на основе короткой стороны
            if( this->succeedPixmap.width() > this->succeedPixmap.height() ){// w / h =mw /  h
                float w =    this->width() * this->succeedPixmap.height() / this->height();
                //Получаем ширину дороги
                p.drawPixmap(QRect(0,0,this->width(),this->height()),this->succeedPixmap,QRect((this->succeedPixmap.width() - w ) / 2,0,w,this->succeedPixmap.height()));
            }else{
                float h =    this->height() * this->succeedPixmap.width() / this->width();
                //Получаем ширину дороги
                p.drawPixmap(QRect(0,0,this->width(),this->height()),this->succeedPixmap,QRect(0,(this->succeedPixmap.height() - h ) / 2,this->succeedPixmap.width(),h));
            }

        }else  if(mStyle == STYLE::percentage){//Сам элемент управления используется в качестве основы
            p.drawPixmap(QRect(0,0,this->width(),this->height()),this->succeedPixmap);
        }else  if(mStyle == STYLE::contain){//以长的为基准
            //На основе длинного
            if(this->succeedPixmap.width() > this->succeedPixmap.height()){
                //Рассчитываем соответствующую высоту
                QPixmap pixmap(this->succeedPixmap.width(), this->height() * this->succeedPixmap.width() / this->width());
                pixmap.fill(Qt::white);//Заливаем прозрачным цветом
                QPainter paint(&pixmap);
                paint.drawPixmap(0,(pixmap.height() - this->succeedPixmap.height()) / 2,this->succeedPixmap.width(),this->succeedPixmap.height(),this->succeedPixmap);
                p.drawPixmap(QRect(0,0 ,this->width(),this->height()),pixmap);
            }else{
                QPixmap pixmap(this->width() * this->succeedPixmap.height() / this->height(),this->succeedPixmap.height());
                pixmap.fill(Qt::white);//Заливаем прозрачным цветом
                QPainter paint(&pixmap);
                paint.drawPixmap((pixmap.width() - this->succeedPixmap.width()) / 2,0,this->succeedPixmap.width(),this->succeedPixmap.height(),this->succeedPixmap);
                p.drawPixmap(QRect(0,0 ,this->width(),this->height()),pixmap);
            }
        }
    }else if(this->mState == STATE::failed){//Ошибка загрузки
        if(mStyle == STYLE::cover){
            //Динамический расчет длинной стороны
            if( this->failedPixmap.width() > this->failedPixmap.height() ){// w / h =mw /  h
                float w =    this->width() * this->failedPixmap.height() / this->height();
                //Получаем ширину дороги
                p.drawPixmap(QRect(0,0,this->width(),this->height()),this->failedPixmap,QRect((this->failedPixmap.width() - w ) / 2,0,w,this->failedPixmap.height()));
            }else{
                float h =    this->height() * this->failedPixmap.width() / this->width();
                //Получаем ширину дороги
                p.drawPixmap(QRect(0,0,this->width(),this->height()),this->failedPixmap,QRect(0,(this->failedPixmap.height() - h ) / 2,this->failedPixmap.width(),h));
            }

        }else if( mStyle == STYLE::percentage){
            p.drawPixmap(QRect(0,0,this->width(),this->height()),this->failedPixmap);
        }else  if(mStyle == STYLE::contain){//На основе длинного
            //Рассчитываем соотношение сторон
            if(this->failedPixmap.width() > this->failedPixmap.height()){
                //Рассчитываем соответствующую высоту
                QPixmap pixmap(this->failedPixmap.width(), this->height() * this->failedPixmap.width() / this->width());
                pixmap.fill(Qt::white);//Заливаем прозрачным цветом
                QPainter paint(&pixmap);
                paint.drawPixmap(0,(pixmap.height() - this->failedPixmap.height()) / 2,this->failedPixmap.width(),this->failedPixmap.height(),this->failedPixmap);
                p.drawPixmap(QRect(0,0 ,this->width(),this->height()),pixmap);
            }else{
                QPixmap pixmap(this->width() * this->failedPixmap.height() / this->height(),this->failedPixmap.height());
                pixmap.fill(Qt::white);//Заливаем прозрачным цветом
                QPainter paint(&pixmap);
                paint.drawPixmap((pixmap.width() - this->failedPixmap.width()) / 2,0,this->failedPixmap.width(),this->failedPixmap.height(),this->failedPixmap);
                p.drawPixmap(QRect(0,0 ,this->width(),this->height()),pixmap);
            }
        }

    }else {//загрузка
        if(mStyle == STYLE::cover){
            //Динамический расчет длинной стороны
            if( this->loadingPixmap.width() > this->loadingPixmap.height() ){// w / h =mw /  h
                float w =    this->width() * this->loadingPixmap.height() / this->height();
                //Ширина дороги
                p.drawPixmap(QRect(0,0,this->width(),this->height()),this->loadingPixmap,QRect((this->loadingPixmap.width() - w ) / 2,0,w,this->loadingPixmap.height()));
            }else{
                float h =    this->height() * this->succeedPixmap.width() / this->width();
                //Ширина дороги
                p.drawPixmap(QRect(0,0,this->width(),this->height()),this->loadingPixmap,QRect(0,(this->loadingPixmap.height() - h ) / 2,this->loadingPixmap.width(),h));
            }

        }else if(mStyle == STYLE::percentage){//За основу взят сам контроль
            p.drawPixmap(QRect(0,0,this->width(),this->height()),this->loadingPixmap);
        }
        else  if(mStyle == STYLE::contain){//На основе длинного
            //Рассчитать соотношение сторон
            if(this->loadingPixmap.width() > this->loadingPixmap.height()){
                //Рассчитайте соответствующую высоту
                QPixmap pixmap(this->loadingPixmap.width(), this->height() * this->loadingPixmap.width() / this->width());
                pixmap.fill(Qt::white);//Заливаем прозрачным цветом
                QPainter paint(&pixmap);
                paint.drawPixmap(0,(pixmap.height() - this->loadingPixmap.height()) / 2,this->loadingPixmap.width(),this->loadingPixmap.height(),this->loadingPixmap);
                p.drawPixmap(QRect(0,0 ,this->width(),this->height()),pixmap);
            }else{
                QPixmap pixmap(this->width() * this->loadingPixmap.height() / this->height(),this->loadingPixmap.height());
                pixmap.fill(Qt::white);//Заливаем прозрачным цветом
                QPainter paint(&pixmap);
                paint.drawPixmap((pixmap.width() - this->loadingPixmap.width()) / 2,0,this->loadingPixmap.width(),this->loadingPixmap.height(),this->loadingPixmap);
                p.drawPixmap(QRect(0,0 ,this->width(),this->height()),pixmap);
            }
        }
    }

}
//Устанавливаем изображение после успешного получения
void ImageView::setSucceedPixmap(QPixmap p)
{
    this->succeedPixmap = p;
    this->mState = STATE::succeed;
    this->repaint();
}
//Устанавливаем загрузочное изображение
void ImageView::setLoadingPixmap(QPixmap p)
{
    this->loadingPixmap = p;
}
//Устанавливаем картинку, отображаемую при сбое загрузки
void ImageView::setFailedPixmap(QPixmap p)
{
    this->failedPixmap = p;

}
//Установить стиль отображения
void ImageView::setDisplayStyle(ImageView::STYLE style)
{
    this->mStyle = style;
}
//Установить путь
void ImageView::setUrl(QString url)
{
    this->mUrl = url;
    //Определите, является ли это сетевым путем
    if(this->mUrl.contains("http://") || this->mUrl.contains("https://") ){//Веб-изображение
        //Определить, есть ли кэш
        QString md5;
        QByteArray bb = QCryptographicHash::hash ( this->mUrl.toUtf8(), QCryptographicHash::Md5 );
        md5.append(bb.toHex());
        QFile file(this->cacheDir+QDir::separator() + md5);
        if(!file.exists()){//Не существует. Зайдите в Интернет.
            qDebug()<<"Загрузка сети";
            this->mState = STATE::loading;
            this->repaint();
            this->mManager->get(QNetworkRequest(url));
        }else{//Существование Go local
            if( file.open(QIODevice::ReadOnly)){
                QByteArray bytes =  file.readAll();
                QPixmap pixmap;
                pixmap.loadFromData(bytes);
                this->setSucceedPixmap(pixmap);
                qDebug()<<"Загрузить локально";
            }else {
                this->mState = STATE::failed;
                repaint();
            }
        }
        file.close();
    }else{//местные фотографии
        this->setSucceedPixmap(QPixmap(url));
    }
}

//Получить изображение после успешной загрузки
QPixmap ImageView::getSucceedPixmap()
{
    return this->succeedPixmap;
}
