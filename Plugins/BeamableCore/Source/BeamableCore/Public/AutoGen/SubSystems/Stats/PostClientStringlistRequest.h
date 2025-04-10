
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamStatsType.h"
#include "BeamableCore/Public/AutoGen/StatUpdateRequestStringListFormat.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PostClientStringlistRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostClientStringlistRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamStatsType ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStatUpdateRequestStringListFormat* Body = {};

	// Beam Base Request Declaration
	UPostClientStringlistRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make PostClientStringlist",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Set,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostClientStringlistRequest* Make(FBeamStatsType _ObjectId, FOptionalArrayOfStatStringListEntry _Set, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostClientStringlistSuccess, FBeamRequestContext, Context, UPostClientStringlistRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostClientStringlistError, FBeamRequestContext, Context, UPostClientStringlistRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostClientStringlistComplete, FBeamRequestContext, Context, UPostClientStringlistRequest*, Request);

using FPostClientStringlistFullResponse = FBeamFullResponse<UPostClientStringlistRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostClientStringlistFullResponse, FPostClientStringlistFullResponse);
