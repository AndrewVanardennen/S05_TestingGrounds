// Fill out your copyright notice in the Description page of Project Settings.

#include "InfinateTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfinateTerrainGameMode::AInfinateTerrainGameMode() 
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bouds Volume Pool"));
}
void AInfinateTerrainGameMode::PopulateBoundsVolumePool()
{
	 TActorIterator<ANavMeshBoundsVolume> VolumeIterator(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}
void AInfinateTerrainGameMode::AddToPool(ANavMeshBoundsVolume * VolumeToAdd)
{
	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}
