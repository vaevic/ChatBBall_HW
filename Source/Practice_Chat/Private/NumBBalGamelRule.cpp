// Fill out your copyright notice in the Description page of Project Settings.


#include "NumBBalGamelRule.h"

void UNumBBalGamelRule::GenerateAnswer()
{
    AnswerNum.Empty();
    TSet<int32> SetNumbers;

    while (SetNumbers.Num() < 3)
    {
        int32 Num = FMath::RandRange(0, 9);
        SetNumbers.Add(Num);
        if (SetNumbers.Contains(Num))
        {
            AnswerNum.Add(Num);
        }
    }
}

FNumBaseballResult UNumBBalGamelRule::CheckAnswer(const FString& Answer) const
{
    FNumBaseballResult Result;
    if (Answer.Len() != 3 || !Answer.IsNumeric())
    {
        Result.bValid = false;
        return Result;
    }

    TArray<TCHAR> CharArray = Answer.GetCharArray();
    CharArray.RemoveAt(CharArray.Num() - 1); // null Á¦°Å

    if (TSet<TCHAR>(CharArray).Num() != 3)
    {
        Result.bValid = false;
        return Result;
    }

    for (int32 i = 0; i < 3; i++)
    {
        int32 Digit = FCString::Atoi(*Answer.Mid(i, 1));

        if (Digit == AnswerNum[i])
        {
            Result.Strikes++;
        }
        else if (AnswerNum.Contains(Digit))
        {
            Result.Balls++;
        }
    }

    return Result;
}