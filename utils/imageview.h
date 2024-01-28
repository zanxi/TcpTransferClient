#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPainter>
#include <QDir>
#include <QFile>
#include <QtDebug>


/**
  * Разработчик: い Бегущая улитка
  * Описание: ImageView поддерживает локальную и сетевую загрузку изображений, а также поддерживает кэширование.
  * Так как первая версия фактически не использовалась в проекте, то могут возникнуть некоторые проблемы и вы можете доработать и расширить ее самостоятельно.
  */

class ImageView : public QWidget
{
    Q_OBJECT
public:
    ImageView(QWidget *parent = 0);
    enum STATE {
        loading,//Маркировка загрузки
        succeed,//Указывает на успешную загрузку
        failed//Указывает, что загрузка не удалась
    };
    enum STYLE {
        cover,//Среднее положение отображается на основе стороны меньшей длины.
        contain,//Отобразите изображение полностью, оставив пустое пространство с обеих сторон.
        percentage//В зависимости от размера элемента управления он будет искажен
    };
public slots:
    void slotReplyPixmapLoad(QNetworkReply *);
protected:
    void paintEvent(QPaintEvent *);//Переопределить методы рисования
private:
    //Атрибуты
    QPixmap loadingPixmap;//загрузка
    QPixmap succeedPixmap;//Загрузка успешно
    QPixmap failedPixmap;//Ошибка загрузки
    int mState;//Отметить статус Загрузка Загрузка успешна Событие загрузки
    int mStyle;//Стиль отображения меток
    QString mUrl;//путь
    QString cacheDir;//каталог кэша
    QNetworkAccessManager *mManager;
    void setSucceedPixmap(QPixmap );//Установите изображения, которые успешно загружаются
public:
    //方法
    void setLoadingPixmap(QPixmap );//Установить загрузочное изображение
    void setFailedPixmap(QPixmap );//Установить изображение с ошибкой загрузки
    void setDisplayStyle(STYLE);//Установить стиль отображения изображения
    void setUrl(QString);//Путь к изображению
    QPixmap getSucceedPixmap();//Получить изображение после успешной загрузки
};

#endif // IMAGEVIEW_H
