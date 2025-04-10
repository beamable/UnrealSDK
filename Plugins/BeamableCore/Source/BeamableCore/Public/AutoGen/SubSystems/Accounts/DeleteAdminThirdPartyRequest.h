
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamAccountId.h"
#include "BeamableCore/Public/AutoGen/DeleteThirdPartyAssociation.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "DeleteAdminThirdPartyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteAdminThirdPartyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamAccountId ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UDeleteThirdPartyAssociation* Body = {};

	// Beam Base Request Declaration
	UDeleteAdminThirdPartyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make DeleteAdminThirdParty",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteAdminThirdPartyRequest* Make(FBeamAccountId _ObjectId, FString _ThirdParty, FString _UserAppId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAdminThirdPartySuccess, FBeamRequestContext, Context, UDeleteAdminThirdPartyRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAdminThirdPartyError, FBeamRequestContext, Context, UDeleteAdminThirdPartyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteAdminThirdPartyComplete, FBeamRequestContext, Context, UDeleteAdminThirdPartyRequest*, Request);

using FDeleteAdminThirdPartyFullResponse = FBeamFullResponse<UDeleteAdminThirdPartyRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteAdminThirdPartyFullResponse, FDeleteAdminThirdPartyFullResponse);
