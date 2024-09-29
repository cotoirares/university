//
// Created by Rares-Andrei Cotoi on 11.07.2024.
//

#include "window.h"

Window::Window(Session& session, Person person, QWidget* parent) : session{session}, person{person}, QWidget{parent} {
    //init session for observer pattern
    session.regObs(this);

    //initial state for widgets
    nameEdit = nullptr;
    descriptionEdit = nullptr;
    latitudeEdit = nullptr;
    longitudeEdit = nullptr;
    dateEdit = nullptr;

    //list layout for widgets
    QVBoxLayout* layout = new QVBoxLayout(this);
    this->setWindowTitle(QString::fromStdString(person.getName()));
    nameLabel = new QLabel{"User name: " + QString::fromStdString(person.getName()), this};
    layout->addWidget(nameLabel);

    locationLabel = new QLabel{"User location: " + QString::number(person.getLocation().first) + ", " + QString::number(person.getLocation().second), this};
    layout->addWidget(locationLabel);

    //list of events
    eventsList = new QListWidget{this};
    if (person.getOrgStatus()) // if the person is an organiser, we solve task 5 and task 6/2
        for (auto& it: session.getEvents()){
            auto item = new QListWidgetItem{QString::fromStdString("Name: " + it.getName() + " Date: " + it.getDate() + " Organiser: " + it.getOrganiser() + " Lat: " + to_string(it.getLocation().first) + " Long: " +
                                                                   to_string(it.getLocation().second)), eventsList};
            if (it.getOrganiser() == person.getName())
                item->setBackground(Qt::green);
        }
    else
        for (auto& it: session.getEvents())
            new QListWidgetItem{QString::fromStdString("Name: " + it.getName() + " Date: " + it.getDate() + " Organiser: " + it.getOrganiser() + " Lat: " + to_string(it.getLocation().first) + " Long: " +
                                                       to_string(it.getLocation().second)), eventsList};
    layout->addWidget(eventsList);

    // checkbox for near events
    nearEvents = new QCheckBox("Near events", this);
    layout->addWidget(nearEvents);
    connect(nearEvents, &QCheckBox::stateChanged, this, &Window::update);
    // add event
    if (person.getOrgStatus()){
        auto descriptionLabel = new QLabel{"Add a new event:", this};
        layout->addWidget(descriptionLabel);

        auto descriptionLabel4 = new QLabel{"Event name:", this};
        layout->addWidget(descriptionLabel4);
        nameEdit = new QLineEdit{"", this};
        layout->addWidget(nameEdit);

        auto descriptionLabel5 = new QLabel{"Event description:", this};
        layout->addWidget(descriptionLabel5);
        descriptionEdit = new QLineEdit{"", this};
        layout->addWidget(descriptionEdit);

        auto descriptionLabel6 = new QLabel{"Event latitude:", this};
        layout->addWidget(descriptionLabel6);
        latitudeEdit = new QLineEdit{"", this};
        layout->addWidget(latitudeEdit);

        auto descriptionLabel7 = new QLabel{"Event longitude:", this};
        layout->addWidget(descriptionLabel7);
        longitudeEdit = new QLineEdit{"", this};
        layout->addWidget(longitudeEdit);

        auto descriptionLabel8 = new QLabel{"Event date:", this};
        layout->addWidget(descriptionLabel8);
        dateEdit = new QLineEdit{"", this};
        layout->addWidget(dateEdit);

        addButton = new QPushButton{"Add event", this};
        layout->addWidget(addButton);

        connect(addButton, &QPushButton::clicked, this, &Window::addEvent);

        //selected event
        auto descriptionLabel1 = new QLabel{"Selected event description (you can modify it)", this};
        layout->addWidget(descriptionLabel1);
        descriptionEdit1 = new QLineEdit{"", this};
        layout->addWidget(descriptionEdit1);
        updateButton = new QPushButton{"Update description", this};
        layout->addWidget(updateButton);

        auto descriptionLabel3 = new QLabel{"Selected event date (you can modify it)", this};
        layout->addWidget(descriptionLabel3);
        dateEdit1 = new QLineEdit{"", this};
        layout->addWidget(dateEdit1);
        updateDateButton = new QPushButton{"Update Date", this};
        layout->addWidget(updateDateButton);

        auto descriptionLabel2 = new QLabel{"Going persons", this};
        layout->addWidget(descriptionLabel2);
        personsList = new QListWidget{this};
        layout->addWidget(personsList);

        mostPopularEvents = new QPushButton{"Show most popular events", this};
        layout->addWidget(mostPopularEvents);

        connect(eventsList, &QListWidget::clicked, this, [this, &session](){
            auto current_event = session.getEvents()[eventsList->currentRow()];
            descriptionEdit1->setText(QString::fromStdString(current_event.getDescription()));
            dateEdit1->setText(QString::fromStdString(current_event.getDate()));
            personsList->clear();
            vector<Person> goingPersons = session.getPersonsGoingToEvent(current_event);
            for (auto& it: goingPersons)
                new QListWidgetItem{QString::fromStdString(it.getName()), personsList};
        });

        connect(updateButton, &QPushButton::clicked, this, [this, &session](){
            session.updateEvent(session.getEvents()[eventsList->currentRow()].getName(), descriptionEdit1->text().toStdString(), session.getEvents()[eventsList->currentRow()].getDate(), session.getEvents()[eventsList->currentRow()].getLocation());
        });

        connect(updateDateButton, &QPushButton::clicked, this, [this, &session](){
            session.updateEvent(session.getEvents()[eventsList->currentRow()].getName(), session.getEvents()[eventsList->currentRow()].getDescription(), dateEdit1->text().toStdString(), session.getEvents()[eventsList->currentRow()].getLocation());
        });

        connect(mostPopularEvents, &QPushButton::clicked, this, [this, &session](){
            auto mostPopular = session.mostPopularEvents();
            auto popup_window = new QWidget{};
            auto layout = new QVBoxLayout{popup_window};
            for (auto& it: mostPopular){
                auto label = new QLabel{QString::fromStdString("Event name: " + it.first.getName()), popup_window};
                layout->addWidget(label);
                auto circle = new QWidget{popup_window};
                circle->setFixedSize(it.second * 10, 10);
                circle->setStyleSheet("background-color: red");
                layout->addWidget(circle);
                auto attendees_label = new QLabel{QString::fromStdString("Number of attendees: " + to_string(it.second)), popup_window};
                layout->addWidget(attendees_label);
            }
            popup_window->show();
        });
    }
    else{
        // show description of selected event
        descriptionEdit = new QLineEdit{"Description:", this};
        layout->addWidget(descriptionEdit);

        goingButton = new QPushButton{"Going", this};
        layout->addWidget(goingButton);

        connect(eventsList, &QListWidget::clicked, this, [this, &session, &person](){
            checkForGoing();
            auto current_event = session.getEvents()[eventsList->currentRow()];
            descriptionEdit->setText(QString::fromStdString(current_event.getDescription()));
        });

        connect(goingButton, &QPushButton::clicked, this, &Window::goingToEvent);
    }
}

void Window::update() const{
    eventsList->clear();
    vector<Event> events = session.getEvents();
    if (nearEvents->isChecked()){
        for (auto& it: events)
            if (sqrt(pow(it.getLocation().first - person.getLocation().first, 2) + pow(it.getLocation().second - person.getLocation().second, 2)) <= 5) {
                auto item = new QListWidgetItem{QString::fromStdString("Name: " + it.getName() + " Date: " + it.getDate() + " Organiser: " + it.getOrganiser() + " Lat: " + to_string(it.getLocation().first) + " Long: " +
                                                                       to_string(it.getLocation().second)), eventsList};
                if (it.getOrganiser() == person.getName())
                    item->setBackground(Qt::green);
            }
    }
    else
        for (auto& it: events) {
            auto item = new QListWidgetItem{QString::fromStdString("Name: " + it.getName() + " Date: " + it.getDate() + " Organiser: " + it.getOrganiser() + " Lat: " + to_string(it.getLocation().first) + " Long: " +
                                                                   to_string(it.getLocation().second)), eventsList};
            if (it.getOrganiser() == person.getName())
                item->setBackground(Qt::green);
        }
}

void Window::clearLabels() {
    nameEdit->clear();
    descriptionEdit->clear();
    latitudeEdit->clear();
    longitudeEdit->clear();
    dateEdit->clear();
}

void Window::addEvent(){
    try{
        session.addEvent(person.getName(), nameEdit->text().toStdString(), descriptionEdit->text().toStdString(), dateEdit->text().toStdString(), std::make_pair(latitudeEdit->text().toDouble(), longitudeEdit->text().toDouble()));
        clearLabels();
    }
    catch (std::exception& e){
        QMessageBox::critical(this, "Error while adding an event", e.what());
    }
    session.notify();
}

void Window::goingToEvent(){
    session.addParticipant(session.getEvents()[eventsList->currentRow()], person);
}

void Window::checkForGoing(){
    bool going = session.isPersonGoingToCertainEvent(session.getEvents()[eventsList->currentRow()], person);
    goingButton->setEnabled(!going);
}

