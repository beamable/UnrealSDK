
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/TransferThirdPartyAssociation.h"
#include "AutoGen/EmptyResponse.h"

#include "PutAdminThirdPartyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAdminThirdPartyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UTransferThirdPartyAssociation* Body;

	// Beam Base Request Declaration
	UPutAdminThirdPartyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutAdminThirdPartyRequest* MakePutAdminThirdPartyRequest(int64 _ObjectId, int64 _FromAccountId, UThirdPartyAssociation* _ThirdParty, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminThirdPartySuccess, FBeamRequestContext, Context, UPutAdminThirdPartyRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminThirdPartyError, FBeamRequestContext, Context, UPutAdminThirdPartyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAdminThirdPartyComplete, FBeamRequestContext, Context, UPutAdminThirdPartyRequest*, Request);

using FPutAdminThirdPartyFullResponse = FBeamFullResponse<UPutAdminThirdPartyRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutAdminThirdPartyFullResponse, FPutAdminThirdPartyFullResponse);
