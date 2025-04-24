
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CooldownModifierRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutListingsCooldownRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutListingsCooldownRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCooldownModifierRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutListingsCooldownRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make PutListingsCooldown",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutListingsCooldownRequest* Make(int64 _ObjectId, int64 _GamerTag, TArray<UUpdateListingCooldownRequestBody*> _UpdateListingCooldownRequests, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutListingsCooldownSuccess, FBeamRequestContext, Context, UPutListingsCooldownRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutListingsCooldownError, FBeamRequestContext, Context, UPutListingsCooldownRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutListingsCooldownComplete, FBeamRequestContext, Context, UPutListingsCooldownRequest*, Request);

using FPutListingsCooldownFullResponse = FBeamFullResponse<UPutListingsCooldownRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutListingsCooldownFullResponse, FPutListingsCooldownFullResponse);
