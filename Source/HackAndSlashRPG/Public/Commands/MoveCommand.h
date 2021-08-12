// Copyright 2021 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Commands/Command.h"
#include "Navigation/PathFollowingComponent.h"

#include "MoveCommand.generated.h"

class UPathFollowingComponent;
/**
 * Move character
 */
UCLASS()
class HACKANDSLASHRPG_API UMoveCommand : public UCommand
{
	GENERATED_BODY()
public:
	void Init(FVector DestinationToSet, ABaseCharacter* OwnerToSet);
	void Init(AActor* DestinationToSet, ABaseCharacter* OwnerToSet);
	virtual void Execute() override;
	virtual bool CanExecute() override;
	virtual void EndExecute() override;

protected:
	UPROPERTY()
	UPathFollowingComponent* PathFollowingComponent;

	FDelegateHandle OnPathCompleteHandle;
	
	UPathFollowingComponent* GetPathFollowingComponent(AController& Controller);

	virtual void OnPathComplete(FAIRequestID RequestID, const FPathFollowingResult& PathFollowingResult);
private:
	UPROPERTY(VisibleAnywhere)
	FVector Destination;

	UPROPERTY(VisibleAnywhere)
	AActor* DestinationActor;
	
};
