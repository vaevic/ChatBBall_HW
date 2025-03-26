// Fill out your copyright notice in the Description page of Project Settings.


#include "NumBaseballGameMode.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "NumBBalGamelRule.h"

ANumBaseballGameMode::ANumBaseballGameMode()
{
    bGameInProgress = false;
}

void ANumBaseballGameMode::StartNewGame()
{
    PlayerStates.Empty();
    bGameInProgress = true;

    Rule = NewObject<UNumBBalGamelRule>();
    Rule->GenerateAnswer();

    UE_LOG(LogTemp, Log, TEXT("[GameMode] New Number Baseball game started."));
}

FString ANumBaseballGameMode::SubmitPlayerInput(const FString& PlayerID, const FString& Input)
{
    UE_LOG(LogTemp, Warning, TEXT("[GameMode] Submit Input From %s: %s"), *PlayerID, *Input);
    
    if (!bGameInProgress || !Rule) return TEXT("게임이 시작되지 않았습니다.");
    
    FString Guess = Input;
    if (Guess.StartsWith(TEXT("/")))
        Guess = Guess.RightChop(1);

    
    if (!PlayerStates.Contains(PlayerID))
    {
        UE_LOG(LogTemp, Warning, TEXT("[Player] New player: %s"), *PlayerID);
        PlayerStates.Add(PlayerID, FPlayerGameState());
    }
        

    FPlayerGameState& State = PlayerStates[PlayerID];
    if (State.bIsWinner)
    {
        UE_LOG(LogTemp, Warning, TEXT("[Early Exit] Already won"));
        return TEXT("You already Win");
    }
    if (State.bIsEliminated)
    {
        UE_LOG(LogTemp, Warning, TEXT("[Early Exit] Already out"));
        return TEXT("You already Over");
    }
    if (State.TryCount >= 3)
    {
        UE_LOG(LogTemp, Warning, TEXT("[Early Exit] Already tried 3 times"));
        return TEXT("You already tried three times.");
    }
      

    State.TryCount++;    

    UE_LOG(LogTemp, Warning, TEXT("[GameMode] Guess after RightChop: %s"), *Guess);

    FNumBaseballResult Result = Rule->CheckAnswer(Guess);
    
    if (!Result.bValid || (Result.Strikes == 0 && Result.Balls == 0))
    {
        State.OutCount++;
        if (State.OutCount >= 3)
            State.bIsEliminated = true;

        CheckGameEnd();
        return Result.ToString();
    }

    if (Result.IsThreeStrike())
    {
        State.bIsWinner = true;
        EndGameWithResult(PlayerID + TEXT("correct Numbers!"));
        return Result.ToString();
    }

    CheckGameEnd();
    return Result.ToString();
}

void ANumBaseballGameMode::CheckGameEnd()
{
    TArray<FString> AlivePlayers;

    for (const auto& Pair : PlayerStates)
    {
        const FPlayerGameState& State = Pair.Value;
        if (!State.bIsEliminated && !State.bIsWinner && State.TryCount < 3)
        {
            AlivePlayers.Add(Pair.Key);
        }
    }

    if (AlivePlayers.Num() == 1)
    {
        EndGameWithResult(AlivePlayers[0] + TEXT(" is Final Player"));
        return;
    }

    bool bAllDone = true;
    for (const auto& Pair : PlayerStates)
    {
        const auto& State = Pair.Value;
        if (!State.bIsEliminated && !State.bIsWinner && State.TryCount < 3)
        {
            bAllDone = false;
            break;
        }
    }

    if (bAllDone)
    {
        EndGameWithResult(TEXT("All Players can't guess Numbers! Draw!"));
    }
}

void ANumBaseballGameMode::EndGameWithResult(const FString& ResultText)
{
    bGameInProgress = false;

    UE_LOG(LogTemp, Warning, TEXT("[Game End] %s"), *ResultText);


    FTimerHandle DelayHandle;
    GetWorld()->GetTimerManager().SetTimer(DelayHandle, this, &ANumBaseballGameMode::StartNewGame, 2.0f, false);
}

