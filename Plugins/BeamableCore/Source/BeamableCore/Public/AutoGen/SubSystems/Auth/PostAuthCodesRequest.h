
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AuthV2AuthCodeRequestBody.h"
#include "BeamableCore/Public/AutoGen/AuthV2AuthCode.h"

#include "PostAuthCodesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostAuthCodesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAuthV2AuthCodeRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostAuthCodesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make PostAuthCodes",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_AccountId,_RedirectUri,_CustomerId,_RealmId,_Context,_Scopes,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostAuthCodesRequest* Make(FOptionalBeamAccountId _AccountId, FOptionalString _RedirectUri, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalAuthV2ContextInfo _Context, FOptionalArrayOfString _Scopes, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostAuthCodesSuccess, FBeamRequestContext, Context, UPostAuthCodesRequest*, Request, UAuthV2AuthCode*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostAuthCodesError, FBeamRequestContext, Context, UPostAuthCodesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostAuthCodesComplete, FBeamRequestContext, Context, UPostAuthCodesRequest*, Request);

using FPostAuthCodesFullResponse = FBeamFullResponse<UPostAuthCodesRequest*, UAuthV2AuthCode*>;
DECLARE_DELEGATE_OneParam(FOnPostAuthCodesFullResponse, FPostAuthCodesFullResponse);
