
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetStorageConnectionRequest.h"

void UGetStorageConnectionRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetStorageConnectionRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/beamo/storage/connection");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetStorageConnectionRequest::BuildBody(FString& BodyString) const
{
	
}

UGetStorageConnectionRequest* UGetStorageConnectionRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetStorageConnectionRequest* Req = NewObject<UGetStorageConnectionRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
