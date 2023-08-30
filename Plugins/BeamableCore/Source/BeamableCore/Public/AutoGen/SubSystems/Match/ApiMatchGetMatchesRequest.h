
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/Match.h"

#include "ApiMatchGetMatchesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiMatchGetMatchesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiMatchGetMatchesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Match", DisplayName="Beam - Make ApiMatchGetMatches",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UApiMatchGetMatchesRequest* Make(FGuid _Id, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiMatchGetMatchesSuccess, FBeamRequestContext, Context, UApiMatchGetMatchesRequest*, Request, UMatch*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiMatchGetMatchesError, FBeamRequestContext, Context, UApiMatchGetMatchesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiMatchGetMatchesComplete, FBeamRequestContext, Context, UApiMatchGetMatchesRequest*, Request);

using FApiMatchGetMatchesFullResponse = FBeamFullResponse<UApiMatchGetMatchesRequest*, UMatch*>;
DECLARE_DELEGATE_OneParam(FOnApiMatchGetMatchesFullResponse, FApiMatchGetMatchesFullResponse);
