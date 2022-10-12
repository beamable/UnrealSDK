
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/CalendarQueryResponse.h"

#include "GetCalendarsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCalendarsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetCalendarsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetCalendarsRequest* MakeGetCalendarsRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCalendarsSuccess, FBeamRequestContext, Context, UGetCalendarsRequest*, Request, UCalendarQueryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCalendarsError, FBeamRequestContext, Context, UGetCalendarsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCalendarsComplete, FBeamRequestContext, Context, UGetCalendarsRequest*, Request);

using FGetCalendarsFullResponse = FBeamFullResponse<UGetCalendarsRequest*, UCalendarQueryResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCalendarsFullResponse, FGetCalendarsFullResponse);
