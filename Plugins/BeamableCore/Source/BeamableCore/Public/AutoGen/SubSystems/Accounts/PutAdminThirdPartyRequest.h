
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamAccountId.h"
#include "BeamableCore/Public/AutoGen/TransferThirdPartyAssociation.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PutAdminThirdPartyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAdminThirdPartyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamAccountId ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UTransferThirdPartyAssociation* Body = {};

	// Beam Base Request Declaration
	UPutAdminThirdPartyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PutAdminThirdParty",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutAdminThirdPartyRequest* Make(FBeamAccountId _ObjectId, int64 _FromAccountId, UThirdPartyAssociation* _ThirdParty, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminThirdPartySuccess, FBeamRequestContext, Context, UPutAdminThirdPartyRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminThirdPartyError, FBeamRequestContext, Context, UPutAdminThirdPartyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAdminThirdPartyComplete, FBeamRequestContext, Context, UPutAdminThirdPartyRequest*, Request);

using FPutAdminThirdPartyFullResponse = FBeamFullResponse<UPutAdminThirdPartyRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutAdminThirdPartyFullResponse, FPutAdminThirdPartyFullResponse);
