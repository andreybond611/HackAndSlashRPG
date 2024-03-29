// Copyright 2022 Andrey Bondarenko. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Utility/RPGEnums.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemDisposition : uint8
{
	None UMETA(DisplayName = "None"),
	Grid UMETA(DisplayName = "Grid"),
	EquipmentSlot UMETA(DisplayName = "EquipmentSlot"),
	PickupMesh UMETA(DisplayName = "PickupMesh")
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
	Rare UMETA(DisplayName = "Rare"),
	Legendary UMETA("Legendary")
};

class UItemGrid;
/**
 * Game item. To create an item, derive a blueprint from this or other
 * abstract item classes. Items can be added to item grids within inventory components,
 * added to an equipment slot, or exist as a pickup mesh.
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew)
class HACKANDSLASHRPG_API UItem : public UObject
{
	GENERATED_BODY()
public:
	void SetGridCoordinates(FIntPoint Coordinates) { GridCoordinates = Coordinates; }
	void SetItemDisposition(EItemDisposition Disposition) { ItemDisposition = Disposition; }
	void SetOwningGrid(UItemGrid* Grid) { OwningGrid = Grid; }

	FText GetItemName()const { return Name; }
	FText GetDescription()const { return Description; }
	UTexture2D* GetImage()const;
	UStaticMesh* GetMesh()const;
	FIntPoint GetSize()const { return Size; }
	FIntPoint GetGridCoordinates()const { return GridCoordinates; }
	EItemRarity GetRarity()const { return Rarity; }
	UItemGrid* GetOwningGrid()const { return OwningGrid; }
	EItemDisposition GetItemDisposition()const { return ItemDisposition; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance", meta = (Multiline = "true", AllowPrivateAccess = "true"))
	FText Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UTexture2D> Image;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UStaticMesh> Mesh;
	// X - Width; Y - Height
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Appearance", meta = (AllowPrivateAccess = "true"))
	FIntPoint Size;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (ClampMin = 1, AllowPrivateAccess = "true"))
	int32 MaxQuantity = 1;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = 1, AllowPrivateAccess = "true"))
	int32 Quantity = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (ClampMin = 0, AllowPrivateAccess = "true"))
	int32 Price;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	EItemRarity Rarity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EItemDisposition ItemDisposition;

	UPROPERTY()
	UItemGrid* OwningGrid;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Grid", meta = (AllowPrivateAccess = "true"))
	FIntPoint GridCoordinates = FIntPoint::NoneValue;

	//TODO: moving in the same grid
	//TODO: dropping items
};
