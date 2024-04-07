/**
 * @file EffectSettings.cpp
 * @brief Implementation of presets and library of effects for the gauntlet.
 */

#include <vector>
#include <map>
#include "EffectLibrary.h"
#include "../../config/config.h"

std::map<EffectLibrary::EffectInst, std::function<BaseEffect *()>> EffectLibrary::effectFactories = {
    {EffectLibrary::EffectInst::BLAST, []()
     { return new Blast(); }},
    {EffectLibrary::EffectInst::PEW, []()
     { return new Pew(); }},
    {EffectLibrary::EffectInst::FLASH, []()
     { return new Flash(); }},
    // Add more effect factories as needed
};

std::vector<EffectLibrary::EffectInst> EffectLibrary::primaryEffects = {
    EffectLibrary::EffectInst::BLAST,
    EffectLibrary::EffectInst::PEW,
    EffectLibrary::EffectInst::FLASH};

std::vector<EffectLibrary::EffectInst> EffectLibrary::secondaryEffects = {
    EffectLibrary::EffectInst::BLAST,
    EffectLibrary::EffectInst::PEW,
    EffectLibrary::EffectInst::FLASH};

std::vector<EffectLibrary::EffectInst> EffectLibrary::specEffects = {
    EffectLibrary::EffectInst::BLAST,
    EffectLibrary::EffectInst::PEW,
    EffectLibrary::EffectInst::FLASH};

std::map<EffectButton, std::vector<EffectLibrary::EffectInst>> EffectLibrary::buttonEffectMap = {
    {PRIMARY_BUTTON, EffectLibrary::primaryEffects},
    {SECONDARY_BUTTON, EffectLibrary::secondaryEffects},
    {SPEC_BUTTON, EffectLibrary::specEffects}};

EffectLibrary::PresetContainer EffectLibrary::action = {EffectInst::BLAST, EffectInst::PEW, EffectInst::FLASH};
