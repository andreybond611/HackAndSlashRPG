// Copyright 2022 Andrey Bondarenko. All rights reserved


#include "Inventory/ItemGrid.h"

#include "Items/Item.h"


void UItemGrid::AllocateCells()
{
	Cells.Reserve(Size.X * Size.Y);

	for (int32 WidthCount = 0; WidthCount < Size.X; ++WidthCount)
	{
		for (int32 HeightCount = 0; HeightCount < Size.Y; ++HeightCount)
		{
			Cells.Add(EMPTY_CELL);
		}
	}
}

UItemGrid* UItemGrid::Create(FIntPoint GridSize)
{
	UItemGrid* NewGrid = NewObject<UItemGrid>();
	NewGrid->Size = GridSize;

	NewGrid->AllocateCells();

	return NewGrid;
}

void UItemGrid::SetCell(FIntPoint Coordinates, uint32 Id)
{
	Cells[GetIndex(Coordinates)] = Id;
}

void UItemGrid::FillArea(FIntPoint TopLeftPoint, FIntPoint AreaSize, uint32 Id)
{
	for (int32 WidthCount = 0; WidthCount < AreaSize.X; ++WidthCount)
	{
		for (int32 HeightCount = 0; HeightCount < AreaSize.Y; ++HeightCount)
		{
			SetCell(FIntPoint(TopLeftPoint.X + WidthCount, TopLeftPoint.Y + HeightCount), Id);
		}
	}
}

FIntPoint UItemGrid::FindEmptyAreaCoordinates(FIntPoint ItemSize)
{
	FIntPoint Result = FIntPoint::NoneValue;

	if (ItemSize.Y > Size.Y || ItemSize.X > Size.X)
		return Result;

	for (int32 HeightCount = 0; HeightCount <= Size.Y - ItemSize.Y; ++HeightCount)
	{
		for (int32 WidthHeight = 0; WidthHeight <= Size.X - ItemSize.X; ++WidthHeight)
		{
			if (IsAreaEmpty(FIntPoint(WidthHeight, HeightCount), ItemSize))
			{
				Result = FIntPoint(WidthHeight, HeightCount);
				return Result;
			}
		}
	}

	return Result;
}

bool UItemGrid::IsAreaEmpty(FIntPoint GridCoordinates, FIntPoint ItemSize) const
{
	bool bResult = true;

	if (GridCoordinates.X + ItemSize.X > Size.X || GridCoordinates.Y + ItemSize.Y > Size.Y)
		return false;

	for (int32 WidthCount = 0; WidthCount < ItemSize.X; ++WidthCount)
	{
		for (int32 HeightCount = 0; HeightCount < ItemSize.Y; ++HeightCount)
		{
			uint32 Cell = GetCell(FIntPoint(GridCoordinates.X + WidthCount, GridCoordinates.Y + HeightCount));
			if (Cell != EMPTY_CELL)
			{
				return false;
			}
		}
	}

	return bResult;
}

void UItemGrid::AddItemInternal(UItem* Item, FIntPoint Coordinates)
{
	Items.Add(Item);
	Item->SetGridCoordinates(Coordinates);
	FillArea(Coordinates, Item->GetSize(), Item->GetUniqueID());
	//OnGridChange.Broadcast();
}

void UItemGrid::RemoveItemInternal(UItem* Item)
{
	Items.Remove(Item);
	Item->SetGridCoordinates(FIntPoint::NoneValue);
	FillArea(Item->GetGridCoordinates(), Item->GetSize(), EMPTY_CELL);
	//OnGridChange.Broadcast();
}