
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetStoragePerformanceRequest.h"

void UGetStoragePerformanceRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetStoragePerformanceRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/storage/performance");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	if(EndDate.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("endDate"), *EndDate.Val);
		bIsFirstQueryParam = false;
	}

	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("storageObjectName"), *StorageObjectName);
	bIsFirstQueryParam = false;
	
	bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
	QueryParams.Appendf(TEXT("%s=%s"), TEXT("granularity"), *Granularity);
	bIsFirstQueryParam = false;
	
	if(StartDate.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("startDate"), *StartDate.Val);
		bIsFirstQueryParam = false;
	}

	if(Period.IsSet){
		bIsFirstQueryParam ? QueryParams.Append(TEXT("?")) : QueryParams.Append(TEXT("&"));
		QueryParams.Appendf(TEXT("%s=%s"), TEXT("period"), *Period.Val);
		bIsFirstQueryParam = false;
	}

	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetStoragePerformanceRequest::BuildBody(FString& BodyString) const
{
	
}

UGetStoragePerformanceRequest* UGetStoragePerformanceRequest::Make(FOptionalString _EndDate, FString _StorageObjectName, FString _Granularity, FOptionalString _StartDate, FOptionalString _Period, UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetStoragePerformanceRequest* Req = NewObject<UGetStoragePerformanceRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	Req->EndDate = _EndDate;
	Req->StorageObjectName = _StorageObjectName;
	Req->Granularity = _Granularity;
	Req->StartDate = _StartDate;
	Req->Period = _Period;
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
