//
// Created by Rares-Andrei Cotoi on 11.07.2024.
//

#include "repository.h"
#include "session.h"
#include "window.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Repository repo;
    Session session(repo);

    for (auto person : repo.getPersons()) {
        Window* wdw = new Window(session, person);
        wdw->show();
    }

    return app.exec();
}