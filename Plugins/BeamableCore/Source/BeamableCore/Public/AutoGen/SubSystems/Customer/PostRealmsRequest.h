
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CreateRealmRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "PostRealmsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostRealmsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCreateRealmRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostRealmsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PostRealms",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bSharded,_Plan,_Parent,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostRealmsRequest* Make(FString _CustomerId, FString _Name, FOptionalBool _bSharded, FOptionalString _Plan, FOptionalString _Parent, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRealmsSuccess, FBeamRequestContext, Context, UPostRealmsRequest*, Request, UEmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRealmsError, FBeamRequestContext, Context, UPostRealmsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostRealmsComplete, FBeamRequestContext, Context, UPostRealmsRequest*, Request);

using FPostRealmsFullResponse = FBeamFullResponse<UPostRealmsRequest*, UEmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPostRealmsFullResponse, FPostRealmsFullResponse);
