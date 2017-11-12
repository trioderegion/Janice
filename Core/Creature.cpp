#include "stdafx.h"
#include "HitPoints.h"
#include "Creature.h"


/**
 * \brief Constructs a Creature (based on Actor)
 * \param name Identifies this creature
 */
ACreature::ACreature(const std::string& name): AActor(name)
{
}
