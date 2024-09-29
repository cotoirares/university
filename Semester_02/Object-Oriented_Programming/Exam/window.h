//
// Created by Rares-Andrei Cotoi on 11.07.2024.
//

#pragma once

#include "repository.h"
#include "observer.h"
#include "session.h"
#include <QPainter>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>
#include <QApplication>
#include <QListWidget>
#include <QCheckBox>
using namespace std;

class Window : public QWidget, public Observer {
Q_OBJECT
private:
    Session &session;
    Person person;
    QLabel *nameLabel, *locationLabel;
    QListWidget *eventsList, *personsList ;
    QCheckBox *nearEvents;
    QLineEdit *nameEdit, *descriptionEdit, *latitudeEdit, *longitudeEdit, *dateEdit, *descriptionEdit1, *dateEdit1;
    QPushButton *addButton, *goingButton, *updateButton, *updateDateButton, *mostPopularEvents;
public:
    Window(Session &session, Person person, QWidget *parent = Q_NULLPTR);
    ~Window() override = default;
    void update() const override;
    void clearLabels();
    void goingToEvent();
    void checkForGoing();
    void addEvent();
};
