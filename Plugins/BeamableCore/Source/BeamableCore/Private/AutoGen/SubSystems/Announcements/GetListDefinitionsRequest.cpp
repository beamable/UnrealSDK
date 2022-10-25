
#include "AutoGen/SubSystems/Announcements/GetListDefinitionsRequest.h"

void UGetListDefinitionsRequest::BuildVerb(FString& VerbString) const
{
	VerbString = TEXT("GET");
}

void UGetListDefinitionsRequest::BuildRoute(FString& RouteString) const
{
	FString Route = TEXT("/basic/announcements/list/definitions");
	
	
	FString QueryParams = TEXT("");
	QueryParams.Reserve(1024);
	bool bIsFirstQueryParam = true;
	
	RouteString.Appendf(TEXT("%s%s"), *Route, *QueryParams);		
}

void UGetListDefinitionsRequest::BuildBody(FString& BodyString) const
{
	
}

UGetListDefinitionsRequest* UGetListDefinitionsRequest::Make(UObject* Outer)
{
	UGetListDefinitionsRequest* Req = NewObject<UGetListDefinitionsRequest>(Outer);

	// Pass in Path and Query Parameters (Blank if no path parameters exist)
	
	
	// Makes a body and fill up with parameters (Blank if no body parameters exist)
	

	return Req;
}
