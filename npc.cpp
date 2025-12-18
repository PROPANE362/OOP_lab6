#include "npc.h"

NPC::NPC(NPCType type, int x, int y, const std::string& name)
    : type(type), x(x), y(y), name(name), alive(true) {
}

NPCType NPC::getType() const {
    return type;
}

int NPC::getX() const {
    return x;
}

int NPC::getY() const {
    return y;
}

const std::string& NPC::getName() const {
    return name;
}

bool NPC::isAlive() const {
    return alive;
}

void NPC::markDead() {
    alive = false;
}

Bear::Bear(int x, int y, const std::string& name)
    : NPC(NPCType::Bear, x, y, name) {
}

Elf::Elf(int x, int y, const std::string& name)
    : NPC(NPCType::Elf, x, y, name) {
}

Rogue::Rogue(int x, int y, const std::string& name)
    : NPC(NPCType::Rogue, x, y, name) {
}