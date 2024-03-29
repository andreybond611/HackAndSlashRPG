// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "StatsAndAttributes/StatCollection.h"
#include "StatsAndAttributes/Stat.h"
#include "StatsAndAttributes/Resource.h"

UStatCollection::UStatCollection()
{
	
}

void UStatCollection::Init()
{
	InitStats();
	InitResources();
	//UpdateResources();
}

void UStatCollection::UpdateResources()
{
	UStat* MaxHealthStat = Stats[EnumToInt(EStat::MaxHealth)];
	UResource* CurrentHealth = Resources[EnumToInt(EResource::Health)];
	MaxHealthStat->OnChange.AddUObject(CurrentHealth, &UResource::OnDependentStatChange);
	CurrentHealth->Value = MaxHealthStat->Get();

	UStat* MaxManaStat = Stats[EnumToInt(EStat::MaxMana)];
	UResource* CurrentMana = Resources[EnumToInt(EResource::Mana)];
	MaxManaStat->OnChange.AddUObject(CurrentMana, &UResource::OnDependentStatChange);
	CurrentMana->Value = MaxManaStat->Get();
}

void UStatCollection::InitResources()
{
	UResource* HealthResource = UResource::Create(100.f, EResource::Health,
	                                              NSLOCTEXT("Stats", "Health", "Current Health"));
	Resources.Insert(HealthResource, EnumToInt(EResource::Health));

	UResource* ManaResource = UResource::Create(100.f, EResource::Mana,
	                                            NSLOCTEXT("Stats", "Mana", "Current Mana"));
	Resources.Insert(ManaResource, EnumToInt(EResource::Mana));
}

void UStatCollection::InitStats()
{
	UStat* ArmorStat = UStat::Create(0.f, EStat::Armor,
	                                 NSLOCTEXT("Stats", "Armor", "Armor"), 0.f, 85.f);
	Stats.Insert(ArmorStat, EnumToInt(EStat::Armor));

	UStat* MaxHealthStat = UStat::Create(100.f, EStat::MaxHealth,
	                                     NSLOCTEXT("Stats", "MaxHealth", "Maximum Health"), 0.f);
	Stats.Insert(MaxHealthStat, EnumToInt(EStat::MaxHealth));

	UStat* MaxManaStat = UStat::Create(100.f, EStat::MaxMana,
	                                   NSLOCTEXT("Stats", "MaxMana", "Maximum Mana"), 0.f);
	Stats.Insert(MaxManaStat, EnumToInt(EStat::MaxMana));

	UStat* MinDamageStat = UStat::Create(10.f, EStat::MinDamage,
	                                     NSLOCTEXT("Stats", "MinDamage", "Minimum Damage"), 0.f);
	Stats.Insert(MinDamageStat, EnumToInt(EStat::MinDamage));

	UStat* MaxDamageStat = UStat::Create(10.f, EStat::MaxDamage,
	                                     NSLOCTEXT("Stats", "MaxDamage", "Maximum Damage"), 0.f);
	Stats.Insert(MaxDamageStat, EnumToInt(EStat::MaxDamage));

	UStat* DamageMultiplierStat = UStat::Create(1.f, EStat::DamageMultiplier,
	                                            NSLOCTEXT("Stats", "DamageMultiplier", "Additional Damage Percent"), 0.01f);
	Stats.Insert(DamageMultiplierStat, EnumToInt(EStat::DamageMultiplier));

	UStat* AttackSpeedStat = UStat::Create(0.f, EStat::AttackSpeed,
	                                       NSLOCTEXT("Stats", "AttackSpeed", "Additional Attack Speed Percent"), -100.f, 75.f);
	Stats.Insert(AttackSpeedStat, EnumToInt(EStat::AttackSpeed));

	UStat* MoveSpeedStat = UStat::Create(100.f, EStat::MoveSpeed,
	                                     NSLOCTEXT("Stats", "MoveSpeed", "Movement Speed"), 0.f, 200.f);
	Stats.Insert(MoveSpeedStat, EnumToInt(EStat::MoveSpeed));

	UStat* HealthRegenStat = UStat::Create(0.f, EStat::HealthRegen,
	                                       NSLOCTEXT("Stats", "HealthRegen", "Health Regeneration"), 0.f);
	Stats.Insert(HealthRegenStat, EnumToInt(EStat::HealthRegen));

	UStat* ManaRegenStat = UStat::Create(0.f, EStat::ManaRegen,
	                                     NSLOCTEXT("Stats", "ManaRegen", "Mana Regeneration"), 0.f);
	Stats.Insert(ManaRegenStat, EnumToInt(EStat::ManaRegen));
}
