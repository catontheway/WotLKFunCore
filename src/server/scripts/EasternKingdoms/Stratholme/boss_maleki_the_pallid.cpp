/* WotLKFunCore is a custom fun server built for
* World of Warcarft game build 3.3.5b. (12345)
*
* Copyright (C) 2008-2016 JustACore.
* Copyright (C) 2008-2016 TrinityCore.
* Copyright (C) 2006-2016 ScriptDev2.
*
* ==== Start of GNU GPL ====
*
* This file is free software; as a special exception the author gives
* unlimited permission to copy and/or distribute it, with or without
* modifications, as long as this notice is preserved.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* ==== End of GNU GPL ====
*/

/* ScriptData
SDName: boss_maleki_the_pallid
SD%Complete: 100
SDComment:
SDCategory: Stratholme
EndScriptData */

#include "ScriptPCH.h"
#include "stratholme.h"

#define SPELL_FROSTBOLT    17503
#define SPELL_DRAINLIFE    20743
#define SPELL_DRAIN_MANA    17243
#define SPELL_ICETOMB    16869

class boss_maleki_the_pallid : public CreatureScript
{
public:
    boss_maleki_the_pallid() : CreatureScript("boss_maleki_the_pallid") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_maleki_the_pallidAI (creature);
    }

    struct boss_maleki_the_pallidAI : public ScriptedAI
    {
        boss_maleki_the_pallidAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = me->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 Frostbolt_Timer;
        uint32 IceTomb_Timer;
        uint32 DrainLife_Timer;

        void Reset()
        {
            Frostbolt_Timer = 1000;
            IceTomb_Timer = 16000;
            DrainLife_Timer = 31000;
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

        void JustDied(Unit* /*killer*/)
        {
            if (instance)
                instance->SetData(TYPE_PALLID, IN_PROGRESS);
        }

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            //Frostbolt
            if (Frostbolt_Timer <= diff)
            {
                 if (rand()%100 < 90)
                    DoCast(me->getVictim(), SPELL_FROSTBOLT);
                Frostbolt_Timer = 3500;
            } else Frostbolt_Timer -= diff;

            //IceTomb
            if (IceTomb_Timer <= diff)
            {
                if (rand()%100 < 65)
                    DoCast(me->getVictim(), SPELL_ICETOMB);
                IceTomb_Timer = 28000;
            } else IceTomb_Timer -= diff;

            //DrainLife
            if (DrainLife_Timer <= diff)
            {
                  if (rand()%100 < 55)
                    DoCast(me->getVictim(), SPELL_DRAINLIFE);
                DrainLife_Timer = 31000;
            } else DrainLife_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };

};

void AddSC_boss_maleki_the_pallid()
{
    new boss_maleki_the_pallid();
}