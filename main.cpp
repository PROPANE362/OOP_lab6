#include "dungeon_editor.h"
#include <iostream>
#include <string>

int main() {
    DungeonEditor editor;
    try {
        editor.addNPC(NPCType::Bear, 100, 100, "Tut_mogla_bit_shutka_pro_BG3");
        editor.addNPC(NPCType::Elf, 150, 150, "Listolub");
        editor.addNPC(NPCType::Rogue, 120, 120, "Nozh_v_jope");
        editor.addNPC(NPCType::Rogue, 130, 130, "Pivo_po_akcii");
        
        editor.printAll();
        
        editor.save("dungeon.txt");
        
        std::cout << "\nStarting battle with range 50..." << std::endl;
        editor.battle(50);
        
        std::cout << "\nSurvivors:" << std::endl;
        editor.printAll();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}