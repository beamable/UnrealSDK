
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/CooldownModifierRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PutListingsCooldownRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutListingsCooldownRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UCooldownModifierRequestBody* Body;

	// Beam Base Request Declaration
	UPutListingsCooldownRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutListingsCooldownRequest* MakePutListingsCooldownRequest(int64 _ObjectId, int64 _GamerTag, TArray<UUpdateListingCooldownRequestBody*> _UpdateListingCooldownRequests, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutListingsCooldownSuccess, FBeamRequestContext, Context, UPutListingsCooldownRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutListingsCooldownError, FBeamRequestContext, Context, UPutListingsCooldownRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutListingsCooldownComplete, FBeamRequestContext, Context, UPutListingsCooldownRequest*, Request);

using FPutListingsCooldownFullResponse = FBeamFullResponse<UPutListingsCooldownRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutListingsCooldownFullResponse, FPutListingsCooldownFullResponse);
