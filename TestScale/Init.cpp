#include "systems.h"
#include <iostream>

using namespace std;

// Реализации методов InitSystem 
void InitSystem::Info() {

    for (int i = 0; i < Emotion.size(); i++) {

        cout << Worlds[i].name << endl;
        cout << "Link: " << Worlds[i].linked_emotion << endl;
        cout << "PortalSize: " << Worlds[i].portal.size() << endl;

        for (int j = 0; j < Worlds[i].portal.size(); j++) {

            cout << "PortaName: " << Worlds[i].portal[j].name << endl;
            cout << "PortalTarget: " << Worlds[i].portal[j].target << endl;

        }
    }
}

void InitSystem::CreateWorlds() {

    for (int i = 0; i < Emotion.size(); i++) {

        Worlds[i].name = Worlds_Names[i];
        Worlds[i].linked_emotion = Emotion[i];

        CreatePortals(Worlds[i].linked_emotion);
    }
}

void InitSystem::CreatePortals(Emotion_ WorldEmotion) {

    for (int i = 0; i < Emotion.size(); i++) {

        if (WorldEmotion == i) {

            for (int j = 0; j < Emotion.size(); j++) {

                if (WorldEmotion != j) {

                    Worlds[WorldEmotion].portal.push_back({ Worlds_Names[j], Emotion[j] });

                }
            }
        }
    }
}