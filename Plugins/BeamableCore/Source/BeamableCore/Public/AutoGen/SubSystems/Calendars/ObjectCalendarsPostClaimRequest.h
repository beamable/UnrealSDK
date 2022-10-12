
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/CalendarClaimRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "ObjectCalendarsPostClaimRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectCalendarsPostClaimRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UCalendarClaimRequestBody* Body;

	// Beam Base Request Declaration
	UObjectCalendarsPostClaimRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UObjectCalendarsPostClaimRequest* MakeObjectCalendarsPostClaimRequest(int64 _ObjectId, FString _Id, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectCalendarsPostClaimSuccess, FBeamRequestContext, Context, UObjectCalendarsPostClaimRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectCalendarsPostClaimError, FBeamRequestContext, Context, UObjectCalendarsPostClaimRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectCalendarsPostClaimComplete, FBeamRequestContext, Context, UObjectCalendarsPostClaimRequest*, Request);

using FObjectCalendarsPostClaimFullResponse = FBeamFullResponse<UObjectCalendarsPostClaimRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectCalendarsPostClaimFullResponse, FObjectCalendarsPostClaimFullResponse);
