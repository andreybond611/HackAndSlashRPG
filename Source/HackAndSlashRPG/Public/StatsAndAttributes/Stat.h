// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Utility/RPGEnums.h"
#include "Stat.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeStat, float);

/**
 * RPG stat ie armor, damage etc. 
 */
UCLASS(BlueprintType)
class HACKANDSLASHRPG_API UStat : public UObject
{
	GENERATED_BODY()
public:
	UStat();

	static UStat* Create(float InInitialValue, EStat InType, FText InName,
		float InMinValue = TNumericLimits<float>::Min(), float InMaxValue = TNumericLimits<float>::Max());

	UFUNCTION(BlueprintPure)
	float Get()const { return ClampedValue; }

	void SetInitialValue(float InInitialValue);
	void SetValue(float InValue);

	/** Call only from modificators */
	UFUNCTION(BlueprintCallable)
	void Add(float Value);
	// TODO: make private, friend modificator class
	/** Call only from modificators */
	UFUNCTION(BlueprintCallable)
	void Remove(float Value);

	FOnChangeStat OnChange;
	
private:
	
	/** To prevent modificators from removing more value than needed when the value is already at max */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float OverflowValue;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ClampedValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float InitialValue = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxValue = TNumericLimits<float>::Max();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MinValue = TNumericLimits<float>::Min();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EStat Type;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FText Name;
};

