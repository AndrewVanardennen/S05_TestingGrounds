// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h" // To know what to do with the BlackboardComponent
#include "AIController.h"
#include "../Public/PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	// TODO protect against empty patrol routes
	

	//UE_LOG(LogTemp, Warning, TEXT("AI in C++ -Woop!"));
	// Get the patrol route
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	// Warn about empty patrol routes
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points"))
			return EBTNodeResult::Failed;
	}

	// Set next waypoint
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	// Cylce the index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	
	return EBTNodeResult::Succeeded;
}
