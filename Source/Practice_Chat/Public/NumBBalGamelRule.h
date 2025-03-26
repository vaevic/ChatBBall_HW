// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NumBBalGamelRule.generated.h"

USTRUCT(BlueprintType)
struct FNumBaseballResult
{
    GENERATED_BODY()

    int32 Strikes = 0;
    int32 Balls = 0;
    bool bValid = true;

    FString ToString() const
    {
        if (!bValid) return TEXT("Wrong input! You got Out point.");
        if (Strikes == 0 && Balls == 0) return TEXT("Out!");

        return FString::Printf(TEXT("S %d, B %d"), Strikes, Balls);
    }

    bool IsThreeStrike() const { return Strikes == 3; }
};

UCLASS()
class PRACTICE_CHAT_API UNumBBalGamelRule : public UObject
{
	GENERATED_BODY()

public:
    
    void GenerateAnswer();    
    FNumBaseballResult CheckAnswer(const FString& Answer) const;

private:
    TArray<int32> AnswerNum; 
};
