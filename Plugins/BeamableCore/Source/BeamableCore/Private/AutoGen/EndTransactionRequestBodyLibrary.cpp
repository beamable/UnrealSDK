
#include "BeamableCore/Public/AutoGen/EndTransactionRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEndTransactionRequestBodyLibrary::EndTransactionRequestBodyToJsonString(const UEndTransactionRequestBody* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UEndTransactionRequestBody* UEndTransactionRequestBodyLibrary::Make(FString Transaction, UObject* Outer)
{
	auto Serializable = NewObject<UEndTransactionRequestBody>(Outer);
	Serializable->Transaction = Transaction;
	
	return Serializable;
}

void UEndTransactionRequestBodyLibrary::Break(const UEndTransactionRequestBody* Serializable, FString& Transaction)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Transaction = Serializable->Transaction;
	}
		
}

