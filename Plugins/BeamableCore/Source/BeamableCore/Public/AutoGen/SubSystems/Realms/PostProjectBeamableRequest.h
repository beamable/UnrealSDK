
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CreateProjectRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostProjectBeamableRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostProjectBeamableRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCreateProjectRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostProjectBeamableRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PostProjectBeamable",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bSharded,_Plan,_Parent,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostProjectBeamableRequest* Make(FString _Name, FOptionalBool _bSharded, FOptionalString _Plan, FOptionalString _Parent, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostProjectBeamableSuccess, FBeamRequestContext, Context, UPostProjectBeamableRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostProjectBeamableError, FBeamRequestContext, Context, UPostProjectBeamableRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostProjectBeamableComplete, FBeamRequestContext, Context, UPostProjectBeamableRequest*, Request);

using FPostProjectBeamableFullResponse = FBeamFullResponse<UPostProjectBeamableRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostProjectBeamableFullResponse, FPostProjectBeamableFullResponse);
