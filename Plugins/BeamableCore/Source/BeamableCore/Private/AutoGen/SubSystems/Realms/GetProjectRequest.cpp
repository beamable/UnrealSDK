
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetProjectRequest.h"

void UGetProjectRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetProjectRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/realms/project");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetProjectRequest::BuildBody(FString& BodyString) const
{
	
}

UGetProjectRequest* UGetProjectRequest::Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders)
{
	UGetProjectRequest* Req = NewObject<UGetProjectRequest>(RequestOwner);
	Req->CustomHeaders = TMap{CustomHeaders};

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
