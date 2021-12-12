// Copyright 2021 Andrey Bondarenko. All rights reserved


#include "GameplayFramework/HackAndSlashPlayerController.h"
#include "Abilities/BasicAttack.h"
#include "Characters/BaseCharacter.h"
#include "Characters/EnemyCharacter.h"
#include "Characters/PlayerCharacter.h"
#include "Components/AbilityComponent.h"
#include "Navigation/PathFollowingComponent.h"

void AHackAndSlashPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AHackAndSlashPlayerController::SetDestination);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AHackAndSlashPlayerController::UnsetDestination);
}

void AHackAndSlashPlayerController::SetDestination()
{
	bIsDestinationSet = true;
}

void AHackAndSlashPlayerController::UnsetDestination()
{
	bIsDestinationSet = false;
	UnsetEnemy();
}

void AHackAndSlashPlayerController::FindPathFollowingComponent()
{
	PathFollowingComp = FindComponentByClass<UPathFollowingComponent>();
	if (PathFollowingComp == nullptr)
	{
		PathFollowingComp = NewObject<UPathFollowingComponent>(this);
		PathFollowingComp->RegisterComponentWithWorld(GetWorld());
		PathFollowingComp->Initialize();
	}
}

void AHackAndSlashPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);

	PlayerAbilityComponent = GetPawn()->FindComponentByClass<UAbilityComponent>();

	AttackAbility = NewObject<UBasicAttack>();

	ControlledCharacter = Cast<APlayerCharacter>(GetCharacter());

	AttackAbility->SetOwner(ControlledCharacter);

	FindPathFollowingComponent();
}

void AHackAndSlashPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsDestinationSet)
	{
		if (Enemy) 
		{
			AttackAbility->SetTargetCharacter(Enemy);
			PlayerAbilityComponent->ExecuteAbility(AttackAbility);
		}
		else 
		{
			FHitResult OutHit;
			if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, OutHit))
			{
				Enemy = Cast<AEnemyCharacter>(OutHit.GetActor());
				if (Enemy)
				{
					return;
				}

				ControlledCharacter->MoveTo(OutHit.Location);
			}
		}
	}
}

void AHackAndSlashPlayerController::AbortMove()
{
	if (PathFollowingComp)
	{
		PathFollowingComp->AbortMove(*GetPawn(), FPathFollowingResultFlags::MovementStop);
	}
}

void AHackAndSlashPlayerController::UnsetEnemy()
{
	Enemy = nullptr;
}
