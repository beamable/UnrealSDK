
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CalendarClaimRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "ObjectCalendarsPostClaimByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectCalendarsPostClaimByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCalendarClaimRequestBody* Body = {};

	// Beam Base Request Declaration
	UObjectCalendarsPostClaimByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Calendars|Utils|Make/Break", DisplayName="Make ObjectCalendarsPostClaimByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectCalendarsPostClaimByObjectIdRequest* Make(int64 _ObjectId, FString _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectCalendarsPostClaimByObjectIdSuccess, FBeamRequestContext, Context, UObjectCalendarsPostClaimByObjectIdRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectCalendarsPostClaimByObjectIdError, FBeamRequestContext, Context, UObjectCalendarsPostClaimByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectCalendarsPostClaimByObjectIdComplete, FBeamRequestContext, Context, UObjectCalendarsPostClaimByObjectIdRequest*, Request);

using FObjectCalendarsPostClaimByObjectIdFullResponse = FBeamFullResponse<UObjectCalendarsPostClaimByObjectIdRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectCalendarsPostClaimByObjectIdFullResponse, FObjectCalendarsPostClaimByObjectIdFullResponse);
