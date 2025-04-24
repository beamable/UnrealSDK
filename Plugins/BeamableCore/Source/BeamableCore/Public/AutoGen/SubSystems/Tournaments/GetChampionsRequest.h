
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/GetChampionsResponse.h"

#include "GetChampionsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetChampionsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id", Category="Beam")
	FString TournamentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cycles", Category="Beam")
	int32 Cycles = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id", Category="Beam")
	FOptionalString ContentId = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetChampionsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make GetChampions",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ContentId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetChampionsRequest* Make(FString _TournamentId, int32 _Cycles, FOptionalString _ContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetChampionsSuccess, FBeamRequestContext, Context, UGetChampionsRequest*, Request, UGetChampionsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetChampionsError, FBeamRequestContext, Context, UGetChampionsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetChampionsComplete, FBeamRequestContext, Context, UGetChampionsRequest*, Request);

using FGetChampionsFullResponse = FBeamFullResponse<UGetChampionsRequest*, UGetChampionsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetChampionsFullResponse, FGetChampionsFullResponse);
