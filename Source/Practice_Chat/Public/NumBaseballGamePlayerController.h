
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
	void Server_ProcessChatMessage(const FString& Message); // ä�� ����ó����

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void Client_DisplayMessage(const FString& Message); // ��� Ŭ���̾�Ʈ ��¿�

	UFUNCTION(BlueprintImplementableEvent)
	void OnDisplayMessage(const FString& Message);
	
};
