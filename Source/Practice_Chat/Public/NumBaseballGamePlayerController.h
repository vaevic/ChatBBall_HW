
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NumBaseballGamePlayerController.generated.h"


UCLASS()
class PRACTICE_CHAT_API ANumBaseballGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_ProcessChatMessage(const FString& Message); // 채팅 서버처리용

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void Client_DisplayMessage(const FString& Message); // 결과 클라이언트 출력용

	UFUNCTION(BlueprintImplementableEvent)
	void OnDisplayMessage(const FString& Message);
	
};
