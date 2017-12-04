/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date November 2017
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include "../include/youbot_gui/qnode.hpp"
#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/youbot_gui/main_window.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <QProcess>
#include <QLCDNumber>
/*****************************************************************************
** Namespaces
*****************************************************************************/





namespace youbot_gui {

using namespace Qt;
using namespace std;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

double min_1 = 0.0100692;
double max_1 = 5.84014;
double MainWindow::joint_1 = 0.0100692;
//static double joint_1 = 0.0100692;

double min_2 = 0.0100692;
double max_2 = 2.61799;
double MainWindow::joint_2 = 0.0100692;

double min_3 = -5.02655;
double max_3 = -0.015708;
double MainWindow::joint_3 = -0.015708;

double min_4 = 0.0221239;
double max_4 = 3.4292;
double MainWindow::joint_4 = 0.0221239;

double min_5 = 0.110619;
double max_5 = 5.64159;
double MainWindow::joint_5 = 0.110619;

double min_6 = 0;
double max_6 = 0.011;
static double gripper_1 = 0;

double min_7 = 0;
double max_7 = 0.011;
static double gripper_2 = 0;


MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
	ui.setupUi(this);
        qnode.ui = ui;
//        qnode.initUi(ui);
    	QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

	setWindowIcon(QIcon(":/images/icon.png"));

    	QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));


        /*********************
        ** Logging
        **********************/
        ui.view_logging->setModel(qnode.loggingModel());
        QObject::connect(&qnode, SIGNAL(loggingUpdated()), this, SLOT(updateLoggingView()));


//        ui.point_window0->setModel(pointsListModel());

}

//void MainWindow::points_list(const std::string &msg)
//{
//          points_list_model.insertRows(points_list_model.rowCount(),1);
//          std::stringstream points_list_model_msg;
//          points_list_model_msg <<
//}

/*MainWindow::MainWindow()//: QMainWindow(parent), qnode(argc,argv)
{}*/

MainWindow::~MainWindow() {}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

void MainWindow::showQ1PlusMsg()
{
	QMessageBox msgBox;
	msgBox.setText("Zwiekszam q1");
	msgBox.exec();
}

void MainWindow::showQ1MinusMsg()
{
	QMessageBox msgBox;
	msgBox.setText("Zmniejszam q1");
	msgBox.exec();
}


void MainWindow::runYoubotDriver()
{
        system("gnome-terminal -x sh -c 'cd ~/youbot ; source devel/setup.bash ; roslaunch youbot_driver_ros_interface youbot_driver.launch'");
}

void MainWindow::on_run_driver_clicked(bool check)
{
        runYoubotDriver();
}

void MainWindow::on_connect_master_clicked(bool check)
{
        qnode.init();
        qnode.czytajPunkty();
        qnode.wyswietl_pkt();
}

void MainWindow::on_fold_clicked(bool check)
{

}

void MainWindow::on_candle_clicked(bool check)
{

}

void MainWindow::on_save_clicked(bool check)
{
    string line[100];
    int line_nmb=0;
    fstream plik;
    fstream plik_temp;
    int nr_pkt = 0;

    plik_temp.open( "punkty.txt", ios::in | ios::out | ios::app);
        if( plik.good() == true )
        {
            while (getline(plik_temp, line[nr_pkt]))
            {
              nr_pkt++;
            }
            plik_temp.close();
        }
        else cout << "Dostep do pliku zostal zabroniony!" << endl;


        plik.open( "punkty.txt", ios::in | ios::out | ios::app);
            if( plik.good() == true )
            {
                cout << "Uzyskano dostep do pliku!" << endl;
                cout<<nr_pkt<<endl;
                //plik << "P0;1;1.1;1.1;1.1;1.1;" << endl;
                plik<<"P"<<nr_pkt+1<<";"<< QNode::subscriber_joint1 <<";"<< QNode::subscriber_joint2 <<";"<< QNode::subscriber_joint3 <<";"
                     << QNode::subscriber_joint4 <<";"<< QNode::subscriber_joint5 <<";"<<endl;
                plik.close();
            }

            else cout << "Dostep do pliku zostal zabroniony!" << endl;
      // cout<< QNode::x;
}


void MainWindow::on_edit_list_clicked(bool check)
{
        //system("gnome-terminal -x sh -c 'cd ~/youbot ; gedit punkty.txt'"); //dodatkowo odpala terminal
        system("bash -c ''cd ~/youbot ; gedit punkty.txt''");   //nie odpala terminala
}
void  MainWindow::on_load_list_clicked(bool check)
{
        qnode.load_points_list();
}

void MainWindow::on_edit_clicked(bool check)
{

        system("bash -c ''cd ~/youbot ; gedit program.txt''");
}
void MainWindow::on_execute_clicked(bool check)
{
      qnode.execute_program();
}
void MainWindow::on_x_plus_clicked(bool check)
{

}
void MainWindow::on_x_minus_clicked(bool check)
{

}
void MainWindow::on_y_plus_clicked(bool check)
{

}
void MainWindow::on_y_minus_clicked(bool check)
{

}
void MainWindow::on_z_plus_clicked(bool check)
{

}
void MainWindow::on_z_minus_clicked(bool check)
{

}

void MainWindow::on_q1_plus_clicked(bool check)
{
        if(joint_1 < max_1 - ((max_1 - min_1)/100))
        joint_1 = joint_1 + (max_1 - min_1)/100;
}

void MainWindow::on_q1_minus_clicked(bool check)
{
        if(joint_1 > min_1 + ((max_1 - min_1)/100))
        joint_1 = joint_1 - (max_1 - min_1)/100;
}

void MainWindow::on_q2_plus_clicked(bool check)
{
        if(joint_2 < max_2 - ((max_2 - min_2)/100))
        joint_2 = joint_2 + (max_2 - min_2)/100;
}

void MainWindow::on_q2_minus_clicked(bool check)
{
        if(joint_2 > min_2 + ((max_2 - min_2)/100))
        joint_2 = joint_2 - (max_2 - min_2)/100;
}

void MainWindow::on_q3_plus_clicked(bool check)
{
        if(joint_3 < max_3 - ((max_3 - min_3)/100))
        joint_3 = joint_3 + (max_3 - min_3)/100;
}

void MainWindow::on_q3_minus_clicked(bool check)
{
        if(joint_3 > min_3 + ((max_3 - min_3)/100))
        joint_3 = joint_3 - (max_3 - min_3)/100;
}

void MainWindow::on_q4_plus_clicked(bool check)
{
        if(joint_4 < max_4 - ((max_4 - min_4)/100))
        joint_4 = joint_4 + (max_4 - min_4)/100;
}

void MainWindow::on_q4_minus_clicked(bool check)
{
        if(joint_4 > min_4 + ((max_4 - min_4)/100))
        joint_4 = joint_4 - (max_4 - min_4)/100;
}

void MainWindow::on_q5_plus_clicked(bool check)
{
        if(joint_5 < max_5 - ((max_5 - min_5)/100))
        joint_5 = joint_5 + (max_5 - min_5)/100;
}

void MainWindow::on_q5_minus_clicked(bool check)
{
        if(joint_5 > min_5 + ((max_5 - min_5)/100))
        joint_5 = joint_5 - (max_5 - min_5)/100;
}



void MainWindow::updateLoggingView() {
        ui.view_logging->scrollToBottom();
}


//komentarz
/*****************************************************************************
** Implementation [Close]
*****************************************************************************/

void MainWindow::closeEvent(QCloseEvent *event)
{
	QMainWindow::closeEvent(event);
}

}  // namespace youbot_gui

