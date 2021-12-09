// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "Abilities/Ability.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Characters/BaseCharacter.h"

DEFINE_LOG_CATEGORY(LogAbility);

void UAbility::Execute()
{
	
}

bool UAbility::CanExecute()
{
	return true;
}

bool UAbility::CanBeQueued()
{
	return true;	
}

float UAbility::DistanceToTarget() const
{
	if (TargetCharacter)
	{
		return Owner->GetDistanceTo(TargetCharacter);
	}
	return FVector::Dist(Owner->GetActorLocation(), TargetLocation);
}

bool UAbility::HasAcceptableDistance() const
{
	return DistanceToTarget() <= MinRange;
}

void UAbility::RunToTarget()
{
	if (TargetCharacter)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToActor(Owner->GetController(), TargetCharacter);
	}
	else
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Owner->GetController(), TargetLocation);
	}
}

void UAbility::StopMoving()
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Owner->GetController(), Owner->GetActorLocation());
}
