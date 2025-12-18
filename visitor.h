#ifndef VISITOR_H
#define VISITOR_H

#include "observer.h"
#include "npc.h"
#include <memory>
#include <vector>

class NPCVisitor {
public:
    NPCVisitor(int range, Observable& observable);

    void visit(Bear& bear);
    void visit(Elf& elf);
    void visit(Rogue& rogue);
    
    void fight(std::vector<std::shared_ptr<NPC>>& npcs);

private:
    int range;
    Observable& observable;
    
    bool inRange(const NPC& a, const NPC& b) const;
    bool canKill(NPCType killer, NPCType victim) const;
};

#endif