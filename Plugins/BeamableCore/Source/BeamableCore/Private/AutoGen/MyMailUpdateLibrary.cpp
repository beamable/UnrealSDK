
#include "BeamableCore/Public/AutoGen/MyMailUpdateLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMyMailUpdateLibrary::MyMailUpdateToJsonString(const UMyMailUpdate* Serializable, const bool Pretty)
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

UMyMailUpdate* UMyMailUpdateLibrary::Make(int64 Id, UUpdateMailRequestBody* Update, UObject* Outer)
{
	auto Serializable = NewObject<UMyMailUpdate>(Outer);
	Serializable->Id = Id;
	Serializable->Update = Update;
	
	return Serializable;
}

void UMyMailUpdateLibrary::Break(const UMyMailUpdate* Serializable, int64& Id, UUpdateMailRequestBody*& Update)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Update = Serializable->Update;
	}
		
}

