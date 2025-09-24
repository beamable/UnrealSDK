#include "Content/BeamContentCacheSerializer.h"

#include "BeamCoreSettings.h"


FArchive& FBeamMemoryWriter::operator<<(struct FSoftObjectPtr& Value)
{
	// Serialize the FName as a string
	if (IsLoading())
	{
		FString Path;
		*this << Path;
		Value = FSoftObjectPath{Path};
	}
	else
	{
		FString Path = Value.ToSoftObjectPath().GetAssetPathString();
		*this << Path;
	}
	return *this;
}

FArchive& FBeamMemoryWriter::operator<<(class UObject*& Res)
{
	bool IsNull = Res == nullptr;

	*this << IsNull;

	if (!IsNull)
	{
		FSoftClassPath PathSoftObject = Res->GetClass();
		FString Path = PathSoftObject.GetAssetPathString();
		*this << Path;
		Res->Serialize(*this);
	}
	return *this;
}

FArchive& FBeamMemoryReader::operator<<(struct FSoftObjectPtr& Value)
{
	// Serialize the FName as a string
	if (IsLoading())
	{
		FString Path;
		*this << Path;
		Value = FSoftObjectPath{Path};
	}
	else
	{
		FString Path = Value.ToSoftObjectPath().GetAssetPathString();
		*this << Path;
	}
	return *this;
}

FArchive& FBeamMemoryReader::operator<<(class UObject*& Res)
{
	bool IsNull = false;

	// Reading if the Res in the serialization was Null 
	*this << IsNull;

	if (!IsNull)
	{
		FString Path = "";
		// Getting the class path to load the target class. 
		*this << Path;
		if (this->IsLoading())
		{
			// Recreate the target UObject and calling the serialize method.
			FSoftClassPath PathSoftObject{Path};
			UClass* Class = PathSoftObject.ResolveClass();

			Res = NewObject<UObject>(GetTransientPackage(), Class);

			if (!ensureAlwaysMsgf(
				Res, TEXT("The deserialization of a un-existent class should be impossible, this means the cache wasn't invalidated. Take a look if you bumped your project version or the SDK version correctly.")))
			{
				return *this;
			}
		}
		Res->Serialize(*this);
	}
	return *this;
}

FBeamContentCacheSerializationContext::FBeamContentCacheSerializationContext(UGameInstance* Instance, bool bIsSaving, FArchive& Ar, const TMap<FString, UClass*>& TypeToContentClass,
                                                                             const TMap<UClass*, FString>& ContentClassToType) : GameInstance(Instance),
                                                                                                                                 bIsSaving(bIsSaving),
                                                                                                                                 TargetAr(Ar),
                                                                                                                                 TypeToContentClass(TypeToContentClass),
                                                                                                                                 ContentClassToType(ContentClassToType)
{
}

bool FBeamContentCacheSerializationContext::IsBakeTime() const
{
	return !GameInstance.IsValid();
}

FArchive* UBeamContentCacheSerializer::GetDefaultContentCacheSerializer(TArray<uint8>& Data, bool bIsSaving)
{
	if (bIsSaving) return new FBeamMemoryWriter(Data, true);
	return new FBeamMemoryReader(Data, true);
}

bool UBeamContentCacheSerializer::SerializeBeamContentCacheHeader(FBeamContentCacheSerializationContext& Ctx)
{
	const auto GetProjectAppVersion = []()
	{
		FString AppVersion;
		GConfig->GetString(TEXT("/Script/EngineSettings.GeneralProjectSettings"), TEXT("ProjectVersion"), AppVersion, GGameIni);
		return AppVersion;
	};


	if (Ctx.TargetAr.IsSaving())
	{
		FString AppVersion = GetProjectAppVersion();

		Ctx.TargetAr << AppVersion;
		Ctx.TargetAr << GetDefault<UBeamCoreSettings>()->BeamableEnvironment->Version;
	}
	else
	{
		FString ProjectAppVersion;
		FString CurrentProjectAppVersion = GetProjectAppVersion();
		Ctx.TargetAr << ProjectAppVersion;

		if (!CurrentProjectAppVersion.Equals(ProjectAppVersion))
		{
			UE_LOG(LogTemp, Warning, TEXT("This cache was created with a different project app version. It cannot be used with this version. So, we are invalidating it. CACHE_VERSION=%s, CURR_VERSION=%s"),
			       *ProjectAppVersion, *CurrentProjectAppVersion);
			return false;
		}

		FBeamPackageVersion SdkVersion;
		FBeamPackageVersion CurrSdkVersion = GetDefault<UBeamCoreSettings>()->BeamableEnvironment->Version;
		Ctx.TargetAr << SdkVersion;
		if (!CurrSdkVersion.Equals(SdkVersion))
		{
			UE_LOG(LogTemp, Warning, TEXT("This cache was created with a different SDK version. It cannot be used with this version. So, we are invalidating it. CACHE_VERSION=%s, CURR_VERSION=%s"),
			       *SdkVersion.ToString(), *CurrSdkVersion.ToString());
			return false;
		}
	}

	return true;
}
