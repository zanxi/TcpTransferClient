#include "dataanimals.h"
#include <QApplication>

void DataSystems::cow_card()
{
    // Дневная запись - карты коров
    dataentry_cow_card_Id = -1;
    dataentry_dataentry_cow_card_animals="";
    dataentry_dataentry_cow_card_responder="";
    dataentry_dataentry_cow_card_name="";
    dataentry_dataentry_cow_card_group="";
    dataentry_dataentry_cow_card_life_number="";
    dataentry_dataentry_cow_card_present="";
    dataentry_dataentry_cow_card_birth_date="";
    dataentry_dataentry_cow_card_location="";
    dataentry_dataentry_cow_card_label="";
    dataentry_dataentry_cow_card_keep="";
    dataentry_dataentry_cow_card_gender="";
    dataentry_dataentry_cow_card_use_as_sire="";
    dataentry_dataentry_cow_card_father_life_number="";
    dataentry_dataentry_cow_card_father_name="";
    dataentry_dataentry_cow_card_mother_life_number="";
    dataentry_dataentry_cow_card_mother_name="";
    dataentry_dataentry_cow_card_hair_color="";
    dataentry_dataentry_cow_card_gestation="";
    dataentry_dataentry_cow_card_calm="";
    dataentry_dataentry_cow_card_blood_type="";
    dataentry_dataentry_cow_card_percentage="";
    dataentry_dataentry_cow_card_description="";
    dataentry_dataentry_cow_card_transfer_in="";
    //QString dataentry_dataentry_cow_card_;
    //QString dataentry_dataentry_cow_card_;
}

void DataSystems::clear_dry_off()
{
    dry_off_animal_No = "";
    //dry_off_number = "";
    dry_off_Robot_number = "";
    dry_off_lactation_number = "";
    dry_off_lactation_days = "";
    dry_off_days_pregnant = "";
    dry_off_day_production = "";
    dry_off_total_day = "";
    dry_off_udder_health_add = "";
    dry_off_udder_health_add_count = "";
}

void DataSystems::clear_insemenation()
{
    Insemenation_animal_No="";
    Insemenation_Robot_number="";
    Insemenation_lactation_number="";
    Insemenation_lactation_days="";
    Insemenation_since_insemenation="";
    Insemenation_insemenation_number="";
    Insemenation_day_production="";
    Insemenation_Activity="";
    Insemenation_days_since_heat="";



}

void DataSystems::clear_batch_transfer()
{

    dataentry_library_batch_transfer_animals="";
    dataentry_library_batch_transfer_responder="";
    dataentry_library_batch_transfer_life_number="";
    dataentry_library_batch_transfer_birth_date="";
    dataentry_library_batch_transfer_location="";
    dataentry_library_batch_transfer_calving_date="";
    dataentry_library_batch_transfer_insemenation_date="";

}



void DataSystems::create_milk_separation()
{

    milk_separation_animal_No="";
    milk_separation_Robot_number="";
    milk_separation_lactation_number="";
    milk_separation_lactation_days="";
    milk_separation_milk_separation_type="";
    milk_separation_milk_separation_tank="";
    milk_separation_end_date="";
    milk_separation_milk_separation_status="";
}

void DataSystems::clear_otel()
{

    // ****************************/////////

    otel_animal_No ="";
    otel_number ="";
    otel_Robot_No ="";
    otel_lactation_No ="";
    otel_lactation_days ="";
    otel_days_pregnant ="";
    otel_lactation_production ="";
    otel_average_lactation ="";
    otel_average_refusals ="";
    otel_average_falures ="";
    otel_average_milk_speed ="";

}

void DataSystems::clear()
{
    // ****************************************************

    //0,125,128 007D80


    settings___color_header="#14B143"; // зеленый (20,177,67)
    settings___color_header___decimal="(20,177,67)"; //    (20,177,67)

    settings___color_header="#FF6C6C"; // красный (255,108,108)
    settings___color_header___decimal="(255,108,108)"; //    (255,108,108)

    settings___color_header="#0683FF"; // синий   (06,131,255)
    settings___color_header___decimal="(06,131,255)"; // синий   (06,131,255)

    settings___color_header="#2222FF"; // синий   (34,34,255)
    settings___color_header___decimal="(34,34,255)"; // синий   (34,34,255)

    //settings___color_header="#FF0000"; // красный (255,0,0)
    //settings___color_header___decimal="(255,0,0)"; //    (255,108,108)

    settings___tabwidget_width="200px";

    // ****************************************************


    db = nullptr;

    log="";
    log_create_db="";
    mj.clear();

    mjpj.clear();
    db_sql.clear();
    db_sql_table_insert.clear();

    //db_check = DB_check::SQLITE;
    db_check = DB_check::PGSQL;
    db_check_create = false;
    //db_check_create = true;
    exit_application = false;

    //db_host="192.168.124.135";
    //db_host="192.168.124.153";
    //db_host="192.168.1.3";
    //db_host="192.168.0.3";
    db_host="127.0.0.1";
    //db_name="vim3";
    db_name="vim3";
    //db_port=5432;
    db_port=5433;
    db_login="postgres";
    //db_login="zanxi";
    db_login="vim";
    //db_login="user1";
    db_date_work="";
    db_generate_random = true;
    //db_generate_random = false;
    id_max=2500;

    db_password="000";
    db_sql_create="create.sql";
    db_sql_insert="insert.sql";
    db_sql_drop="drop.sql";
    db_sqlite_file = "c://lely//db-lely3.db";
    db_sqlite_file_autorization = QApplication::applicationDirPath()+"/"+ "autorization_user_data.db";
    //db_sqlite_file="c://db-prolely3.db";
    //db_sqlite_file="db-test.db";
    //db_sqlite_file="003.db";

    db_connection_counter = 0;

    name_animals="корова";

    y=0;

    savePath = QApplication::applicationDirPath();

    //********************************

    dataentry_robot_counter = 0;
    dataentry_cow_card_counter = 0;
    dataentry_transfer_counter = 0;
    dataentry_otel_counter = 0;
    dataentry_insemenation_counter = 0;
    dataentry_dry_off_counter = 0;
    dataentry_milk_separation_counter = 0;
    dataentry_milk_settings_counter = 0;

    //1_1


    DataService_Id = -1;
    DataService_FarmDepart= "";
    DataService_counrty= "";
    DataService_lang= "";
    DataService_culture= "";
    DataService_Index;
    DataService_street= "";
    DataService_street_number= "";
    DataService_zip_code= "";
    DataService_city= "";
    DataService_telephone= "";
    DataService_owner_name= "";

    // Дневная запись - карты коров
    dataentry_cow_card_Id = -1;
    dataentry_dataentry_cow_card_animals="";
    dataentry_dataentry_cow_card_responder="";
    dataentry_dataentry_cow_card_name="";
    dataentry_dataentry_cow_card_group="";
    dataentry_dataentry_cow_card_life_number="";
    dataentry_dataentry_cow_card_present="";
    dataentry_dataentry_cow_card_birth_date="";
    dataentry_dataentry_cow_card_location="";
    dataentry_dataentry_cow_card_label="";
    dataentry_dataentry_cow_card_keep="";
    dataentry_dataentry_cow_card_gender="";
    dataentry_dataentry_cow_card_use_as_sire="";
    dataentry_dataentry_cow_card_father_life_number="";
    dataentry_dataentry_cow_card_father_name="";
    dataentry_dataentry_cow_card_mother_life_number="";
    dataentry_dataentry_cow_card_mother_name="";
    dataentry_dataentry_cow_card_hair_color="";
    dataentry_dataentry_cow_card_gestation="";
    dataentry_dataentry_cow_card_calm="";
    dataentry_dataentry_cow_card_blood_type="";
    dataentry_dataentry_cow_card_percentage="";
    dataentry_dataentry_cow_card_description="";
    dataentry_dataentry_cow_card_transfer_in="";
    //QString dataentry_dataentry_cow_card_;
    //QString dataentry_dataentry_cow_card_;

    transfer_animal_No="";
    transfer_number="";
    transfer_Robot_No="";
    transfer_lactation_No="";
    transfer_lactation_days="";
    transfer_days_pregnant="";
    transfer_present="";




    dataentry_library_Id = -1;
    dataentry_library_siries_number= "";
    dataentry_library_siries_sire_name= "";
    dataentry_library_siries_life_number= "";
    dataentry_library_siries_sire_code= "";
    dataentry_library_siries_active= "";

    dataentry_library_feed_types_number_feed_types= "";
    dataentry_library_feed_types_dry_matter= "";
    dataentry_library_feed_types_name= "";
    dataentry_library_feed_types_active= "";
    dataentry_library_feed_types_type= "";
    dataentry_library_feed_types_remark= "";

    dataentry_library_batch_transfer_animals="";
    dataentry_library_batch_transfer_responder="";
    dataentry_library_batch_transfer_life_number="";
    dataentry_library_batch_transfer_birth_date="";
    dataentry_library_batch_transfer_location="";
    dataentry_library_batch_transfer_calving_date="";
    dataentry_library_batch_transfer_insemenation_date="";

   // ****************************************


    // ****************************/////////

    otel_animal_No ="";
    otel_number ="";
    otel_Robot_No ="";
    otel_lactation_No ="";
    otel_lactation_days ="";
    otel_days_pregnant ="";
    otel_lactation_production ="";
    otel_average_lactation ="";
    otel_average_refusals ="";
    otel_average_falures ="";
    otel_average_milk_speed ="";
    // расширенные
    otel_current_location =""; // 1 calving
    otel_days_dry ="";
    otel_waiting_time_dry_off ="";
    otel_remarks_previous ="";
    otel_expected_calving ="";
    otel_calving_date ="";
    otel_waiting_time_colostrum ="";
    otel_number_of_calves ="";
    otel_remarks ="";
    otel_group ="";
    otel_cow_number ="";
    otel_responder ="";
    otel_teat ="";
    otel_separation_milk_tank ="";
    otel_calf_born_dead =""; // 2 calf 1
    otel_calf_keep_calf ="";
    otel_calf_calf_number ="";
    otel_calf_life_number ="";
    otel_calf_name ="";
    otel_calf_weight ="";
    otel_calf_sex ="";
    otel_calf_hair_color ="";
    otel_calf_group ="";


   // ***************************

    dry_off_animal_No = "";
    //dry_off_number = "";
    dry_off_Robot_number = "";
    dry_off_lactation_number = "";
    dry_off_lactation_days = "";
    dry_off_days_pregnant = "";
    dry_off_day_production = "";
    dry_off_total_day = "";
    dry_off_udder_health_add = "";
    dry_off_udder_health_add_count = "";

    dry_off_date = "";
    dry_off_medicine_used = "";
    dry_off_medicine_category = "";
    dry_off_medicine = "";
    dry_off_dosage = "";
    dry_off_Teat_LF = "";
    dry_off_Teat_RF = "";
    dry_off_Teat_LR = "";
    dry_off_Teat_RR = "";
    dry_off_separate_meat_untill = "";
    dry_off_separate_milk_untill = "";
    dry_off_group = "";


    // *********************************

    Insemenation_animal_No="";
    Insemenation_Robot_number="";
    Insemenation_lactation_number="";
    Insemenation_lactation_days="";
    Insemenation_since_insemenation="";
    Insemenation_insemenation_number="";
    Insemenation_day_production="";
    Insemenation_Activity="";
    Insemenation_days_since_heat="";

    Insemenation_expected_otel="";



    Insemenation_date="";
    Insemenation_sire="";
    Insemenation_person="";
    Insemenation_group="";
    Insemenation_remarks="";


    // *************************************

    milk_separation_animal_No="";
    milk_separation_Robot_number="";
    milk_separation_lactation_number="";
    milk_separation_lactation_days="";
    milk_separation_milk_separation_type="";
    milk_separation_milk_separation_tank="";
    milk_separation_end_date="";
    milk_separation_milk_separation_status="";
    milk_separation_start_separation_y="";
    milk_separation_start_separation_h="";
    milk_separation_end_separation_y="";
    milk_separation_end_separation_h="";
    milk_separation_expected_dry="";


    //*********************

    milk_settings_animal_No="";
    milk_settings_Robot_number="";
    milk_settings_lactation_number="";
    milk_settings_lactation_days="";
    milk_settings_priority_feeding="";
    milk_settings_milk_teat_lf="";
    milk_settings_milk_teat_lr="";
    milk_settings_milk_teat_rf="";
    milk_settings_milk_teat_rr="";
    milk_settings_milk_under_supervision="";
    milk_settings_training_period="";

    //*********************

    routing_animal_No="";
    routing_Robot_number="";
    routing_lactation_number="";
    routing_lactation_days="";
    routing_area="";
    routing_from_date="";
    routing_till_date="";
    routing_from_till_time="";
    routing_active_routing="";

    //*********************

    robot_robot_no = "";
    robot_coord_teat_lf = "";
    robot_coord_teat_lr = "";
    robot_coord_teat_rf = "";
    robot_coord_teat_rr = "";
    robot_param1 = "";
    robot_param2 = "";
    robot_param3 = "";
    robot_param4 = "";
    robot_paramtime1 = "";
    robot_paramtime2 = "";
    robot_paramtime3 = "";
    robot_paramtime4 = "";
    robot_paramfile1 = nullptr;
    robot_paramfile2 = nullptr;
    robot_paramfilephoto1 = "";
    robot_paramfilephoto2 = "";
    robot_paramfilephoto3 = "";
    robot_paramfilephoto4 = "";


    //************************

    dataentry_settings____milking__general_milking__colostrum_day = "";
    dataentry_settings____milking__general_milking__milk_destination = "";
    dataentry_settings____milking__general_milking__separation_milk_destination = "";
    dataentry_settings____milking__general_milking__milk_teat_lf = "";
    dataentry_settings____milking__general_milking__milk_teat_lr = "";
    dataentry_settings____milking__general_milking__milk_teat_rf = "";
    dataentry_settings____milking__general_milking__milk_teat_rr = "";
    dataentry_settings____milking__general_milking__reset_teat_coordinates_aftre_dry = "";
    dataentry_settings____milking__general_milking__training_period = "";
    dataentry_settings____milking__general_milking__milk_under_supervision = "";
    dataentry_settings____milking__general_milking__optimal_sampling_period = "";
    dataentry_settings____milking__general_milking__teat_position_known = "";
    dataentry_settings____milking__general_milking__correction_time = "";
    dataentry_settings____milking__general_milking__alternative_connection_method = "";

    //*********************

    dataentry_settings____milking__post_milking__number_of_treatments_lf = "";
    dataentry_settings____milking__post_milking__number_of_treatments_lr = "";
    dataentry_settings____milking__post_milking__number_of_treatments_rf = "";
    dataentry_settings____milking__post_milking__number_of_treatments_rr = "";
    dataentry_settings____milking__post_milking__duration_per_treatment_lf = "";
    dataentry_settings____milking__post_milking__duration_per_treatment_lr = "";
    dataentry_settings____milking__post_milking__duration_per_treatment_rf = "";
    dataentry_settings____milking__post_milking__duration_per_treatment_rr = "";
    dataentry_settings____milking__post_milking__clean_milk_equipment = "";
    dataentry_settings____milking__post_milking__priority_feeding = "";


    //*********************

    fixed_feeding_animal_No = "";
    fixed_feeding_name = "";
    fixed_feeding_group_ = "";
    fixed_feeding_days_in = "";
    fixed_feeding_days_feed = "";
    fixed_feeding_milk_yield = "";
    fixed_feeding_mb_markant = "";
    fixed_feeding_mb_focus = "";
    fixed_feeding_transition = "";


    // ************** Ввод данных ->  Дневная запись -> Взятие проб у партии (Batch Sampling) *********************

    dataentry_dataentry__Batch_Sampling__animal_No = "";
    dataentry_dataentry__Batch_Sampling__milk_yield = "";
    dataentry_dataentry__Batch_Sampling__fat = "";
    dataentry_dataentry__Batch_Sampling__protein = "";
    dataentry_dataentry__Batch_Sampling__standard_peak_production = "";
    dataentry_dataentry__Batch_Sampling__SCC = ""; // SCC (количество соматических клетов)


    // ************** Ввод данных ->  Дневная запись -> Кондиция партии (Batch condition) ***************************

    dataentry_dataentry__Batch_condition__number = "";
    dataentry_dataentry__Batch_condition__claw = "";
    dataentry_dataentry__Batch_condition__body = "";
    dataentry_dataentry__Batch_condition__breast = "";
    dataentry_dataentry__Batch_condition__weight = "";







    //*********************

    RIndication_RecordId = "";
    RIndication_Type = "";
    RIndication_IndicationId = "";
    RIndication_CreationTime = "";
    RIndication_DTViewed = "";
    RIndication_Parameter1 = "";
    RIndication_Parameter2 = "";
    RIndication_Parameter3 = "";
    RIndication_Parameter4 = "";



    //*********************

    RTransmitBuffer_Dest = "";
    RTransmitBuffer_Code = "";
    RTransmitBuffer_Crc = "";
    RTransmitBuffer_Length = "";
    RTransmitBuffer_TabId = "";
    RTransmitBuffer_D00 = "";
    RTransmitBuffer_D01 = "";
    RTransmitBuffer_D02 = "";
    RTransmitBuffer_D03 = "";
    RTransmitBuffer_D04 = "";
    RTransmitBuffer_D05 = "";
    RTransmitBuffer_D06 = "";
    RTransmitBuffer_D07 = "";
    RTransmitBuffer_D08 = "";
    RTransmitBuffer_D09 = "";
    RTransmitBuffer_D10 = "";
    RTransmitBuffer_D11 = "";
    RTransmitBuffer_D12 = "";
    RTransmitBuffer_D13 = "";
    RTransmitBuffer_D14 = "";
    RTransmitBuffer_D15 = "";
    RTransmitBuffer_D16 = "";
    RTransmitBuffer_D17 = "";
    RTransmitBuffer_D18 = "";
    RTransmitBuffer_D19 = "";
    RTransmitBuffer_D20 = "";
    RTransmitBuffer_D21 = "";
    RTransmitBuffer_D22 = "";
    RTransmitBuffer_D23 = "";
    RTransmitBuffer_D24 = "";
    RTransmitBuffer_D25 = "";
    RTransmitBuffer_D26 = "";
    RTransmitBuffer_D27 = "";
    RTransmitBuffer_D28 = "";
    RTransmitBuffer_D29 = "";
    RTransmitBuffer_D30 = "";
    RTransmitBuffer_D31 = "";
    RTransmitBuffer_D32 = "";
    RTransmitBuffer_D33 = "";
    RTransmitBuffer_D34 = "";
    RTransmitBuffer_D35 = "";
    RTransmitBuffer_D36 = "";
    RTransmitBuffer_D37 = "";
    RTransmitBuffer_D38 = "";
    RTransmitBuffer_D39 = "";
    RTransmitBuffer_D40 = "";
    RTransmitBuffer_D41 = "";
    RTransmitBuffer_D42 = "";
    RTransmitBuffer_D43 = "";
    RTransmitBuffer_D44 = "";
    RTransmitBuffer_D45 = "";
    RTransmitBuffer_D46 = "";
    RTransmitBuffer_D47 = "";
    RTransmitBuffer_D48 = "";
    RTransmitBuffer_D49 = "";
    RTransmitBuffer_D50 = "";
    RTransmitBuffer_D51 = "";
    RTransmitBuffer_D52 = "";
    RTransmitBuffer_D53 = "";
    RTransmitBuffer_D54 = "";
    RTransmitBuffer_D55 = "";
    RTransmitBuffer_D56 = "";
    RTransmitBuffer_D57 = "";
    RTransmitBuffer_D58 = "";
    RTransmitBuffer_D59 = "";
    RTransmitBuffer_D60 = "";
    RTransmitBuffer_D61 = "";
    RTransmitBuffer_D62 = "";
    RTransmitBuffer_D63 = "";
    RTransmitBuffer_D64 = "";
    RTransmitBuffer_D65 = "";
    RTransmitBuffer_D66 = "";
    RTransmitBuffer_D67 = "";
    RTransmitBuffer_D68 = "";
    RTransmitBuffer_D69 = "";
    RTransmitBuffer_D70 = "";
    RTransmitBuffer_D71 = "";
    RTransmitBuffer_D72 = "";
    RTransmitBuffer_D73 = "";
    RTransmitBuffer_D74 = "";
    RTransmitBuffer_D75 = "";
    RTransmitBuffer_D76 = "";
    RTransmitBuffer_D77 = "";
    RTransmitBuffer_D78 = "";
    RTransmitBuffer_D79 = "";
    RTransmitBuffer_D80 = "";
    RTransmitBuffer_D81 = "";
    RTransmitBuffer_D82 = "";
    RTransmitBuffer_D83 = "";
    RTransmitBuffer_D84 = "";
    RTransmitBuffer_D85 = "";
    RTransmitBuffer_D86 = "";
    RTransmitBuffer_D87 = "";
    RTransmitBuffer_D88 = "";
    RTransmitBuffer_D89 = "";
    RTransmitBuffer_D90 = "";
    RTransmitBuffer_D91 = "";
    RTransmitBuffer_D92 = "";
    RTransmitBuffer_D93 = "";
    RTransmitBuffer_D94 = "";
    RTransmitBuffer_D95 = "";
    RTransmitBuffer_D96 = "";
    RTransmitBuffer_D97 = "";
    RTransmitBuffer_D98 = "";
    RTransmitBuffer_D99 = "";
    RTransmitBuffer_D100 = "";
    RTransmitBuffer_D101 = "";
    RTransmitBuffer_D102 = "";
    RTransmitBuffer_D103 = "";
    RTransmitBuffer_D104 = "";
    RTransmitBuffer_D105 = "";
    RTransmitBuffer_D106 = "";
    RTransmitBuffer_D107 = "";
    RTransmitBuffer_D108 = "";
    RTransmitBuffer_D109 = "";
    RTransmitBuffer_D110 = "";
    RTransmitBuffer_D111 = "";
    RTransmitBuffer_D112 = "";
    RTransmitBuffer_D113 = "";
    RTransmitBuffer_D114 = "";
    RTransmitBuffer_D115 = "";
    RTransmitBuffer_D116 = "";
    RTransmitBuffer_D117 = "";
    RTransmitBuffer_D118 = "";
    RTransmitBuffer_D119 = "";
    RTransmitBuffer_D120 = "";
    RTransmitBuffer_D121 = "";
    RTransmitBuffer_D122 = "";
    RTransmitBuffer_D123 = "";
    RTransmitBuffer_D124 = "";
    RTransmitBuffer_D125 = "";
    RTransmitBuffer_D126 = "";
    RTransmitBuffer_D127 = "";
    RTransmitBuffer_D128 = "";
    RTransmitBuffer_D129 = "";
    RTransmitBuffer_D130 = "";
    RTransmitBuffer_D131 = "";
    RTransmitBuffer_D132 = "";
    RTransmitBuffer_D133 = "";
    RTransmitBuffer_D134 = "";
    RTransmitBuffer_D135 = "";
    RTransmitBuffer_D136 = "";
    RTransmitBuffer_D137 = "";
    RTransmitBuffer_D138 = "";
    RTransmitBuffer_D139 = "";
    RTransmitBuffer_D140 = "";
    RTransmitBuffer_D141 = "";
    RTransmitBuffer_D142 = "";
    RTransmitBuffer_D143 = "";
    RTransmitBuffer_D144 = "";
    RTransmitBuffer_D145 = "";
    RTransmitBuffer_D146 = "";
    RTransmitBuffer_D147 = "";
    RTransmitBuffer_D148 = "";
    RTransmitBuffer_D149 = "";
    RTransmitBuffer_D150 = "";
    RTransmitBuffer_D151 = "";
    RTransmitBuffer_D152 = "";
    RTransmitBuffer_D153 = "";
    RTransmitBuffer_D154 = "";
    RTransmitBuffer_D155 = "";
    RTransmitBuffer_D156 = "";
    RTransmitBuffer_D157 = "";
    RTransmitBuffer_D158 = "";
    RTransmitBuffer_D159 = "";
    RTransmitBuffer_D160 = "";
    RTransmitBuffer_D161 = "";
    RTransmitBuffer_D162 = "";
    RTransmitBuffer_D163 = "";
    RTransmitBuffer_D164 = "";
    RTransmitBuffer_D165 = "";
    RTransmitBuffer_D166 = "";
    RTransmitBuffer_D167 = "";
    RTransmitBuffer_D168 = "";
    RTransmitBuffer_D169 = "";
    RTransmitBuffer_D170 = "";
    RTransmitBuffer_D171 = "";
    RTransmitBuffer_D172 = "";
    RTransmitBuffer_D173 = "";
    RTransmitBuffer_D174 = "";
    RTransmitBuffer_D175 = "";
    RTransmitBuffer_D176 = "";
    RTransmitBuffer_D177 = "";
    RTransmitBuffer_D178 = "";
    RTransmitBuffer_D179 = "";
    RTransmitBuffer_D180 = "";
    RTransmitBuffer_D181 = "";
    RTransmitBuffer_D182 = "";
    RTransmitBuffer_D183 = "";
    RTransmitBuffer_D184 = "";
    RTransmitBuffer_D185 = "";
    RTransmitBuffer_D186 = "";
    RTransmitBuffer_D187 = "";
    RTransmitBuffer_D188 = "";
    RTransmitBuffer_D189 = "";
    RTransmitBuffer_D190 = "";
    RTransmitBuffer_D191 = "";
    RTransmitBuffer_D192 = "";
    RTransmitBuffer_D193 = "";
    RTransmitBuffer_D194 = "";
    RTransmitBuffer_D195 = "";
    RTransmitBuffer_D196 = "";
    RTransmitBuffer_D197 = "";
    RTransmitBuffer_D198 = "";
    RTransmitBuffer_D199 = "";
    RTransmitBuffer_D150_ = "";
    RTransmitBuffer_D151_ = "";
    RTransmitBuffer_D152_ = "";
    RTransmitBuffer_D153_ = "";
    RTransmitBuffer_D154_ = "";
    RTransmitBuffer_D155_ = "";
    RTransmitBuffer_D156_ = "";
    RTransmitBuffer_D157_ = "";
    RTransmitBuffer_D158_ = "";
    RTransmitBuffer_D159_ = "";
    RTransmitBuffer_D160_ = "";
    RTransmitBuffer_D161_ = "";
    RTransmitBuffer_D162_ = "";
    RTransmitBuffer_D163_ = "";
    RTransmitBufferD164_ = "";


    //*******************************************


    RMilkSettings_TagId = "";
    RMilkSettings_StructId = "";
    RMilkSettings_MilkingAllowed = "";
    RMilkSettings_CreationTime = "";
    RMilkSettings_MinMilkInterval = "";
    RMilkSettings_ForcedCleaning = "";
    RMilkSettings_MilkAction = "";
    RMilkSettings_MilkDestination = "";
    RMilkSettings_SCCSampling = "";
    RMilkSettings_TakeOffMethod = "";
    RMilkSettings_PulsMethodMilking = "";
    RMilkSettings_MilkMethod = "";
    RMilkSettings_MilkSampling = "";
    RMilkSettings_Calved = "";
    RMilkSettings_AltConnMethod = "";
    RMilkSettings_VacuumLevel = "";
    RMilkSettings_MaxConnectTime = "";
    RMilkSettings_MaxConnections = "";
    RMilkSettings_CleaningOrder = "";
    RMilkSettings_CleaningTimeLR = "";
    RMilkSettings_CleaningTimeRR = "";
    RMilkSettings_CleaningTimeRF = "";
    RMilkSettings_CleaningTimeLF = "";
    RMilkSettings_CleaningIterLR = "";
    RMilkSettings_CleaningIterRR = "";
    RMilkSettings_CleaningIterRF = "";
    RMilkSettings_CleaningIterLF = "";
    RMilkSettings_PulsFreqLR = "";
    RMilkSettings_PulsFreqRR = "";
    RMilkSettings_PulsFreqRF = "";
    RMilkSettings_PulsFreqLF = "";
    RMilkSettings_PulsRatioLR = "";
    RMilkSettings_PulsRatioRR = "";
    RMilkSettings_PulsRatioRF = "";
    RMilkSettings_PulsRatioLF = "";
    RMilkSettings_DisIterLR = "";
    RMilkSettings_DisIterRR = "";
    RMilkSettings_DisIterRF = "";
    RMilkSettings_DisIterLF = "";
    RMilkSettings_DisTimeLR = "";
    RMilkSettings_DisTimeRR = "";
    RMilkSettings_DisTimeRF = "";
    RMilkSettings_DisTimeLF = "";
    RMilkSettings_BlockTimeStart1 = "";
    RMilkSettings_BlockDuration1 = "";
    RMilkSettings_BlockTimeStart2 = "";
    RMilkSettings_BlockDuration2 = "";
    RMilkSettings_StartTimeMilkSampling = "";
    RMilkSettings_StartTimeSCCSampling = "";


    //******************************************************


    RFeedVisit_TagId = "";
    RFeedVisit_StructId = "";
    RFeedVisit_NrOfFeedTypes = "";
    RFeedVisit_VisitId = "";
    RFeedVisit_SeqNr = "";
    RFeedVisit_StartFeedVisitTime = "";
    RFeedVisit_EndFeedVisitTime = "";
    RFeedVisit_SettingTime = "";
    RFeedVisit_TroughId = "";
    RFeedVisit_Free = "";
    RFeedVisit_RemindTime = "";
    RFeedVisit_RemindTrough = "";
    RFeedVisit_CowType = "";
    RFeedVisit_StuffRate = "";
    RFeedVisit_FeedId1 = "";
    RFeedVisit_Nu1 = "";
    RFeedVisit_LastFeedVisitTime1 = "";
    RFeedVisit_CurrentPeriodAmount1 = "";
    RFeedVisit_Credit1 = "";
    RFeedVisit_TakeIn1 = "";
    RFeedVisit_FeedId2 = "";
    RFeedVisit_Nu2 = "";
    RFeedVisit_LastFeedVisitTime2 = "";
    RFeedVisit_CurrentPeriodAmount2 = "";
    RFeedVisit_Credit2 = "";
    RFeedVisit_TakeIn2 = "";
    RFeedVisit_FeedId3 = "";
    RFeedVisit_Nu3 = "";
    RFeedVisit_LastFeedVisitTime3 = "";
    RFeedVisit_CurrentPeriodAmount3 = "";
    RFeedVisit_Credit3 = "";
    RFeedVisit_TakeIn3 = "";
    RFeedVisit_FeedId4 = "";
    RFeedVisit_NU4 = "";
    RFeedVisit_LastFeedVisitTime4 = "";
    RFeedVisit_CurrentPeriodAmount4 = "";
    RFeedVisit_Credit4 = "";
    RFeedVisit_TakeIn4 = "";
    RFeedVisit_FeedId5 = "";
    RFeedVisit_NU5 = "";
    RFeedVisit_LastFeedVisitTime5 = "";
    RFeedVisit_CurrentPeriodAmount5 = "";
    RFeedVisit_Credit5 = "";
    RFeedVisit_TakeIn5 = "";
    RFeedVisit_FeedId6 = "";
    RFeedVisit_NU6 = "";
    RFeedVisit_LastFeedVisitTime6 = "";
    RFeedVisit_CurrentPeriodAmount6 = "";
    RFeedVisit_Credit6 = "";
    RFeedVisit_TakeIn6 = "";
    RFeedVisit_FeedId7 = "";
    RFeedVisit_NU7 = "";
    RFeedVisit_LastFeedVisitTime7 = "";
    RFeedVisit_CurrentPeriodAmount7 = "";
    RFeedVisit_Credit7 = "";
    RFeedVisit_TakeIn7 = "";
    RFeedVisit_FeedId8 = "";
    RFeedVisit_NU8 = "";
    RFeedVisit_LastFeedVisitTime8 = "";
    RFeedVisit_CurrentPeriodAmount8 = "";
    RFeedVisit_Credit8 = "";
    RFeedVisit_TakeIn8 = "";
    RFeedVisit_FeedId9 = "";
    RFeedVisit_NU9 = "";
    RFeedVisit_LastFeedVisitTime9 = "";
    RFeedVisit_CurrentPeriodAmount9 = "";
    RFeedVisit_Credit9 = "";
    RFeedVisit_TakeIn9 = "";
    RFeedVisit_Free_ = "";

    //*******************

    RMilkVisit_TagId = "";
    RMilkVisit_StructId = "";
    RMilkVisit_ChangedSettings = "";
    RMilkVisit_VisitId = "";
    RMilkVisit_SettingTime = "";
    RMilkVisit_StartMilkVisitTime = "";
    RMilkVisit_EndMilkVisitTime = "";
    RMilkVisit_LastSucceedMilkTime = "";
    RMilkVisit_MilkingResult = "";
    RMilkVisit_ConsecFailes = "";
    RMilkVisit_AvgVisitTime = "";
    RMilkVisit_MilkYield = "";
    RMilkVisit_MilkYieldExp = "";
    RMilkVisit_BottleNumber = "";
    RMilkVisit_RackNumber = "";
    RMilkVisit_MilkTemperature = "";
    RMilkVisit_MilkSpeedMax = "";
    RMilkVisit_DeadMilkTimeLR = "";
    RMilkVisit_DeadMilkTimeRR = "";
    RMilkVisit_DeadMilkTimeRF = "";
    RMilkVisit_DeadMilkTimeLF = "";
    RMilkVisit_DeadMilkTimeAvgLR = "";
    RMilkVisit_DeadMilkTimeAvgRR = "";
    RMilkVisit_DeadMilkTimeAvgRF = "";
    RMilkVisit_DeadMilkTimeAvgLF = "";
    RMilkVisit_MilkTimeLR = "";
    RMilkVisit_MilkTimeRR = "";
    RMilkVisit_MilkTimeRF = "";
    RMilkVisit_MilkTimeLF = "";
    RMilkVisit_YieldLR = "";
    RMilkVisit_YieldRR = "";
    RMilkVisit_YieldRF = "";
    RMilkVisit_YieldLF = "";
    RMilkVisit_RankLR = "";
    RMilkVisit_RankRR = "";
    RMilkVisit_RankRF = "";
    RMilkVisit_RankLF = "";
    RMilkVisit_RankDevLR = "";
    RMilkVisit_RankDevRR = "";
    RMilkVisit_RankDevRF = "";
    RMilkVisit_RankDevLF = "";
    RMilkVisit_XPosAvgLR = "";
    RMilkVisit_XPosAvgRR = "";
    RMilkVisit_XPosAvgRF = "";
    RMilkVisit_XPosAvgLF = "";
    RMilkVisit_YPosAvgLR = "";
    RMilkVisit_YPosAvgRR = "";
    RMilkVisit_YPosAvgRF = "";
    RMilkVisit_YPosAvgLF = "";
    RMilkVisit_ZPosAvgLR = "";
    RMilkVisit_ZPosAvgRR = "";
    RMilkVisit_ZPosAvgRF = "";
    RMilkVisit_ZPosAvgLF = "";
    RMilkVisit_LengthLR = "";
    RMilkVisit_LengthRR = "";
    RMilkVisit_LengthRF = "";
    RMilkVisit_LengthLF = "";
    RMilkVisit_WidthLR = "";
    RMilkVisit_WidthRR = "";
    RMilkVisit_WidthRF = "";
    RMilkVisit_WidthLF = "";
    RMilkVisit_AttachmentsLR = "";
    RMilkVisit_AttachmentsRR = "";
    RMilkVisit_AttachmentsRF = "";
    RMilkVisit_AttachmentsLF = "";
    RMilkVisit_ConductivityLR = "";
    RMilkVisit_ConductivityRR = "";
    RMilkVisit_ConductivityRF = "";
    RMilkVisit_ConductivityLF = "";
    RMilkVisit_ConductivityMAvgLR = "";
    RMilkVisit_ConductivityMAvgRR = "";
    RMilkVisit_ConductivityMAvgRF = "";
    RMilkVisit_ConductivityMAvgLF = "";
    RMilkVisit_RedReflectionLR = "";
    RMilkVisit_RedReflectionRR = "";
    RMilkVisit_RedReflectionRF = "";
    RMilkVisit_RedReflectionLF = "";
    RMilkVisit_GreenReflectionLR = "";
    RMilkVisit_GreenReflectionRR = "";
    RMilkVisit_GreenReflectionRF = "";
    RMilkVisit_GreenReflectionLF = "";
    RMilkVisit_BlueReflectionLR = "";
    RMilkVisit_BlueReflectionRR = "";
    RMilkVisit_BlueReflectionRF = "";
    RMilkVisit_BlueReflectionLF = "";
    RMilkVisit_BackColorLR = "";
    RMilkVisit_BackColorRR = "";
    RMilkVisit_BackColorRF = "";
    RMilkVisit_BackColorLF = "";
    RMilkVisit_AttMastitis = "";
    RMilkVisit_AttBlood = "";
    RMilkVisit_AttColostrum = "";
    RMilkVisit_AttAbnormal = "";
    RMilkVisit_AttFirstMilkAbnormal = "";
    RMilkVisit_AttConductivity = "";
    RMilkVisit_AvgMilkPerHourLR = "";
    RMilkVisit_AvgMilkPerHourRR = "";
    RMilkVisit_AvgMilkPerHourRF = "";
    RMilkVisit_AvgMilkPerHourLF = "";
    RMilkVisit_FailedMilkYieldLR = "";
    RMilkVisit_FailedMilkYieldRR = "";
    RMilkVisit_FailedMilkYieldRF = "";
    RMilkVisit_FailedMilkYieldLF = "";
    RMilkVisit_AvgMilkTimePHourLR = "";
    RMilkVisit_AvgMilkTimePHourRR = "";
    RMilkVisit_AvgMilkTimePHourRF = "";
    RMilkVisit_AvgMilkTimePHourLF = "";
    RMilkVisit_FailedMilkTimeLR = "";
    RMilkVisit_FailedMilkTimeRR = "";
    RMilkVisit_FailedMilkTimeRF = "";
    RMilkVisit_FailedMilkTimeLF = "";
    RMilkVisit_MilkDestination = "";
    RMilkVisit_MilkDestReason = "";
    RMilkVisit_PreTreatmentTime = "";
    RMilkVisit_ConnectTime = "";
    RMilkVisit_PostTreatmentTime = "";
    RMilkVisit_MilkTime = "";
    RMilkVisit_CurrentNrMilkSamples = "";
    RMilkVisit_UdderScansNr = "";
    RMilkVisit_UdderScanTime = "";
    RMilkVisit_RearScansNr = "";
    RMilkVisit_FrontScansNr = "";
    RMilkVisit_RearScanTime = "";
    RMilkVisit_FrontScanTime = "";
    RMilkVisit_AttachmentTimeLR = "";
    RMilkVisit_AttachmentTimeRR = "";
    RMilkVisit_AttachmentTimeRF = "";
    RMilkVisit_AttachmentTimeLF = "";
    RMilkVisit_WaitTimeLelyWash = "";
    RMilkVisit_WaitTimeMilkJar = "";
    RMilkVisit_SCC_DrainTimeLR = "";
    RMilkVisit_SCC_DrainTimeRR = "";
    RMilkVisit_SCC_DrainTimeRF = "";
    RMilkVisit_SCC_DrainTimeLF = "";
    RMilkVisit_CurrentNrSCCSamples = "";
    RMilkVisit_Free1 = "";
    RMilkVisit_LastMilkSamplingTime = "";


    //*********************************************

    RVisitTab_TagId = "";
    RVisitTab_StructId = "";
    RVisitTab_Result = "";
    RVisitTab_StartVisitTime = "";
    RVisitTab_EndVisitTime = "";
    RVisitTab_AnimalWeight = "";
    RVisitTab_AnimalActivity = "";
    RVisitTab_SeqNr = "";
    RVisitTab_ChangedSettings = "";
    RVisitTab_Free = "";
    RVisitTab_UserWaitTime = "";


    //*****************************************************


    RFeedSettings_TagId = "";
    RFeedSettings_StructId = "";
    RFeedSettings_FeedingSettings = "";
    RFeedSettings_CowId         = "";
    RFeedSettings_CreationTime = "";
    RFeedSettings_FeedAlgorithm = "";
    RFeedSettings_NrOfFeedTypes = "";
    RFeedSettings_ConnectFailFactor = "";
    RFeedSettings_Free = "";
    RFeedSettings_FeedId1 = "";
    RFeedSettings_DoseStratic1 = "";
    RFeedSettings_BlockTimeStart1 = "";
    RFeedSettings_BlockTimeDuration1 = "";
    RFeedSettings_AmountProHour1 = "";
    RFeedSettings_FeedSpeed1 = "";
    RFeedSettings_MinPeriodAmount1 = "";
    RFeedSettings_MaxCredit1 = "";
    RFeedSettings_MaxPeriodAmount1 = "";
    RFeedSettings_FeedId2 = "";
    RFeedSettings_DoseStratic2 = "";
    RFeedSettings_BlockTimeStart2 = "";
    RFeedSettings_BlockTimeDuration2 = "";
    RFeedSettings_AmountProHour2 = "";
    RFeedSettings_FeedSpeed2 = "";
    RFeedSettings_MinPeriodAmount2 = "";
    RFeedSettings_MaxCredit2 = "";
    RFeedSettings_MaxPeriodAmount2 = "";
    RFeedSettings_FeedId13 = "";
    RFeedSettings_DoseStratic3 = "";
    RFeedSettings_BlockTimeStart3 = "";
    RFeedSettings_BlockTimeDuration3 = "";
    RFeedSettings_AmountProHour3 = "";
    RFeedSettings_FeedSpeed3 = "";
    RFeedSettings_MinPeriodAmount3 = "";
    RFeedSettings_MaxCredit3 = "";
    RFeedSettings_MaxPeriodAmount3 = "";
    RFeedSettings_FeedId4 = "";
    RFeedSettings_DoseStratic4 = "";
    RFeedSettings_BlockTimeStart4 = "";
    RFeedSettings_BlockTimeDuration4 = "";
    RFeedSettings_AmountProHour4 = "";
    RFeedSettings_FeedSpeed4 = "";
    RFeedSettings_MinPeriodAmount4 = "";
    RFeedSettings_MaxCredit4 = "";
    RFeedSettings_MaxPeriodAmount4 = "";
    RFeedSettings_FeedId5 = "";
    RFeedSettings_DoseStratic5 = "";
    RFeedSettings_BlockTimeStart5 = "";
    RFeedSettings_BlockTimeDuration5 = "";
    RFeedSettings_AmountProHour5 = "";
    RFeedSettings_FeedSpeed5 = "";
    RFeedSettings_MinPeriodAmount5 = "";
    RFeedSettings_MaxCredit5 = "";
    RFeedSettings_MaxPeriodAmount5 = "";
    RFeedSettings_FeedId6 = "";
    RFeedSettings_DoseStratic6 = "";
    RFeedSettings_BlockTimeStart6 = "";
    RFeedSettings_BlockTimeDuration6 = "";
    RFeedSettings_AmountProHour6 = "";
    RFeedSettings_FeedSpeed6 = "";
    RFeedSettings_MinPeriodAmount6 = "";
    RFeedSettings_MaxCredit6 = "";
    RFeedSettings_MaxPeriodAmount6 = "";
    RFeedSettings_FeedId7 = "";
    RFeedSettings_DoseStratic7 = "";
    RFeedSettings_BlockTimeStart7 = "";
    RFeedSettings_BlockTimeDuration7 = "";
    RFeedSettings_AmountProHour7 = "";
    RFeedSettings_FeedSpeed7 = "";
    RFeedSettings_MinPeriodAmount7 = "";
    RFeedSettings_MaxCredit7 = "";
    RFeedSettings_MaxPeriodAmount7 = "";
    RFeedSettings_FeedId8 = "";
    RFeedSettings_DoseStratic8 = "";
    RFeedSettings_BlockTimeStart8 = "";
    RFeedSettings_BlockTimeDuration8 = "";
    RFeedSettings_AmountProHour8 = "";
    RFeedSettings_FeedSpeed8 = "";
    RFeedSettings_MinPeriodAmount8 = "";
    RFeedSettings_MaxCredit8 = "";
    RFeedSettings_MaxPeriodAmount8 = "";
    RFeedSettings_FeedId9 = "";
    RFeedSettings_DoseStratic9 = "";
    RFeedSettings_BlockTimeStart9 = "";
    RFeedSettings_BlockTimeDuration9 = "";
    RFeedSettings_AmountProHour9 = "";
    RFeedSettings_FeedSpeed9 = "";
    RFeedSettings_MinPeriodAmount9 = "";
    RFeedSettings_MaxCredit9 = "";
    RFeedSettings_MaxPeriodAmount9 = "";

    //********************************************


    RGWSettings_TagId = "";
    RGWSettings_StructId = "";
    RGWSettings_Free = "";
    RGWSettings_CreationTime = "";
    RGWSettings_MinMilkInt = "";
    RGWSettings_MinMilkIntGrazing = "";
    RGWSettings_CowSelectionSettings = "";
    RGWSettings_NrOfCowSeparations = "";
    RGWSettings_ManualDestPrio = "";
    RGWSettings_ManualDest = "";
    RGWSettings_ManualDestStartTime = "";
    RGWSettings_ManualDestDuration = "";
    RGWSettings_MilkNowPrio = "";
    RGWSettings_MilkNowDest = "";
    RGWSettings_MilkNowStartTime = "";
    RGWSettings_MilkNowDuration = "";
    RGWSettings_NearMilkPrio = "";
    RGWSettings_NearMilkDest = "";
    RGWSettings_NearMilkingStartTime = "";
    RGWSettings_NearMilkDuration = "";
    RGWSettings_MilkedPrio = "";
    RGWSettings_MilkedDest = "";
    RGWSettings_MilkedStartTime = "";
    RGWSettings_MilkedDuration = "";
    RGWSettings_FailedMilkPrio = "";
    RGWSettings_FailedMilkDest = "";
    RGWSettings_FailedMilkStartTime = "";
    RGWSettings_FailedMilkDuration = "";
    RGWSettings_NrFailedMilksPrio = "";
    RGWSettings_NrFailedMilksDest = "";
    RGWSettings_NrFailedMilkStartTime = "";
    RGWSettings_NrFailedMilkDuration = "";
    RGWSettings_GrazingAPrio = "";
    RGWSettings_GrazingADest = "";
    RGWSettings_GrazingAStartTime = "";
    RGWSettings_GrazingADuration = "";
    RGWSettings_GrazingBPrio = "";
    RGWSettings_GrazingBDest = "";
    RGWSettings_GrazingBStartTime = "";
    RGWSettings_GrazingBDuration = "";
    RGWSettings_GrazingCPrio = "";
    RGWSettings_GrazingCDest = "";
    RGWSettings_GrazingCStartTime = "";
    RGWSettings_GrazingCDuration = "";
    RGWSettings_GrazingDPrio = "";
    RGWSettings_GrazingDDest = "";
    RGWSettings_GrazingDStartTime = "";
    RGWSettings_GrazingDDuration = "";
    RGWSettings_Free_1 = "";
    RGWSettings_Free_2 = "";










}
