
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetStoragePerformanceByStorageObjectNameRequest.h"

void UApiBeamoGetStoragePerformanceByStorageObjectNameRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UApiBeamoGetStoragePerformanceByStorageObjectNameRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/api/beamo/storage/{storageObjectName}/performance");
	Route = Route.Replace(TEXT("{storageObjectName}"), *StorageObjectName);
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(Period.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("Period"), *Period.Val);
		bIsFirstQueryParam = false;
	}

	if(StartTime.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("StartTime"), *StartTime.Val.ToIso8601());
		bIsFirstQueryParam = false;
	}

	if(EndTime.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("EndTime"), *EndTime.Val.ToIso8601());
		bIsFirstQueryParam = false;
	}

	if(Granularity.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("Granularity"), *Granularity.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UApiBeamoGetStoragePerformanceByStorageObjectNameRequest::BuildBody(FString& BodyString) const
{
	
}

UApiBeamoGetStoragePerformanceByStorageObjectNameRequest* UApiBeamoGetStoragePerformanceByStorageObjectNameRequest::Make(FString _StorageObjectName, FOptionalString _Period, FOptionalDateTime _StartTime, FOptionalDateTime _EndTime, FOptionalString _Granularity, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UApiBeamoGetStoragePerformanceByStorageObjectNameRequest* Req = NewObject<UApiBeamoGetStoragePerformanceByStorageObjectNameRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->StorageObjectName = _StorageObjectName;
	Req->Period = _Period;
	Req->StartTime = _StartTime;
	Req->EndTime = _EndTime;
	Req->Granularity = _Granularity;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
