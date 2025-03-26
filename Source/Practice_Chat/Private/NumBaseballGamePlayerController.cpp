// Fill out your copyright notice in the Description page of Project Settings.


#include "NumBaseballGamePlayerController.h"
#include "NumBaseballGameMode.h"
#include "GameFramework/PlayerState.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

void ANumBaseballGamePlayerController::Server_ProcessChatMessage_Implementation(const FString& Message)
{
    UE_LOG(LogTemp, Warning, TEXT("Raw Message: %s"), *Message);

    if (!Message.StartsWith(TEXT("/"))) return;

    FString Guess = Message.RightChop(1);

    UE_LOG(LogTemp, Warning, TEXT("Guess: %s"), *Guess);

    AGameModeBase* GM = GetWorld()->GetAuthGameMode();
    ANumBaseballGameMode* BaseballGM = Cast<ANumBaseballGameMode>(GM);

    if (BaseballGM)
    {
        FString PlayerID = GetPlayerState<APlayerState>()->GetPlayerName();
        FString Result = BaseballGM->SubmitPlayerInput(PlayerID, Guess);
        Client_DisplayMessage(Result);
    }

    
}

void ANumBaseballGamePlayerController::Client_DisplayMessage_Implementation(const FString& Message)
{
    OnDisplayMessage(Message);
}


