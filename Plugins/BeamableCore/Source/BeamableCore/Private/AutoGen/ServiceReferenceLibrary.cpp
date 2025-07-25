
#include "BeamableCore/Public/AutoGen/ServiceReferenceLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServiceReferenceLibrary::ServiceReferenceToJsonString(const UServiceReference* Serializable, const bool Pretty)
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

UServiceReference* UServiceReferenceLibrary::Make(bool bArchived, bool bArm, bool bEnabled, FString ServiceName, FString Checksum, FString TemplateId, FString ImageId, FOptionalInt64 ContainerHealthCheckPort, FOptionalString ImageCpuArch, FOptionalString Comments, FOptionalArrayOfServiceComponent Components, FOptionalArrayOfServiceDependencyReference Dependencies, UObject* Outer)
{
	auto Serializable = NewObject<UServiceReference>(Outer);
	Serializable->bArchived = bArchived;
	Serializable->bArm = bArm;
	Serializable->bEnabled = bEnabled;
	Serializable->ServiceName = ServiceName;
	Serializable->Checksum = Checksum;
	Serializable->TemplateId = TemplateId;
	Serializable->ImageId = ImageId;
	Serializable->ContainerHealthCheckPort = ContainerHealthCheckPort;
	Serializable->ImageCpuArch = ImageCpuArch;
	Serializable->Comments = Comments;
	Serializable->Components = Components;
	Serializable->Dependencies = Dependencies;
	
	return Serializable;
}

void UServiceReferenceLibrary::Break(const UServiceReference* Serializable, bool& bArchived, bool& bArm, bool& bEnabled, FString& ServiceName, FString& Checksum, FString& TemplateId, FString& ImageId, FOptionalInt64& ContainerHealthCheckPort, FOptionalString& ImageCpuArch, FOptionalString& Comments, FOptionalArrayOfServiceComponent& Components, FOptionalArrayOfServiceDependencyReference& Dependencies)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bArchived = Serializable->bArchived;
		bArm = Serializable->bArm;
		bEnabled = Serializable->bEnabled;
		ServiceName = Serializable->ServiceName;
		Checksum = Serializable->Checksum;
		TemplateId = Serializable->TemplateId;
		ImageId = Serializable->ImageId;
		ContainerHealthCheckPort = Serializable->ContainerHealthCheckPort;
		ImageCpuArch = Serializable->ImageCpuArch;
		Comments = Serializable->Comments;
		Components = Serializable->Components;
		Dependencies = Serializable->Dependencies;
	}
		
}

