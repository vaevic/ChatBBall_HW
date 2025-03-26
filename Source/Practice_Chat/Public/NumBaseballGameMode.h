// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NumBaseballGameMode.generated.h"

class UNumBBalGamelRule;

USTRUCT()
struct FPlayerGameState
{
    GENERATED_BODY()

    int32 TryCount = 0;
    int32 OutCount = 0;
    bool bIsEliminated = false;
    bool bIsWinner = false;
};


UCLASS()
class PRACTICE_CHAT_API ANumBaseballGameMode : public AGameMode
{
	GENERATED_BODY()

public:
    ANumBaseballGameMode();

    // ä�� �Է� ó�� (��Ʈ�ѷ����� ȣ��)
    FString SubmitPlayerInput(const FString& PlayerID, const FString& Input);

protected:
    UFUNCTION(BlueprintCallable, Category = "Number Baseball")
    void StartNewGame();
    void CheckGameEnd();
    void EndGameWithResult(const FString& ResultText);

private:
    UPROPERTY()
    UNumBBalGamelRule* Rule;

    TMap<FString, FPlayerGameState> PlayerStates;
    bool bGameInProgress = false;
	
};
