#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_MyTestCPP.generated.h"


UCLASS()
class PRACTICE_CHAT_API UBP_MyTestCPP : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MyTestCPPLib")
	static FString GetMyFirstCPP();
};