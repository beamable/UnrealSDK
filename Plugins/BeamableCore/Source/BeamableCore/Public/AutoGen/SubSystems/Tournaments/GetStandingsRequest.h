
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/GetStandingsResponse.h"

#include "GetStandingsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStandingsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id")
	FString TournamentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max")
	FOptionalInt32 Max;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Focus")
	FOptionalInt64 Focus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cycle")
	FOptionalInt32 Cycle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From")
	FOptionalInt32 From;

	// Body Params
	

	// Beam Base Request Declaration
	UGetStandingsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Max,_Focus,_Cycle,_From,Outer"))
	static UGetStandingsRequest* MakeGetStandingsRequest(FString _TournamentId, FOptionalInt32 _Max, FOptionalInt64 _Focus, FOptionalInt32 _Cycle, FOptionalInt32 _From, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStandingsSuccess, FBeamRequestContext, Context, UGetStandingsRequest*, Request, UGetStandingsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStandingsError, FBeamRequestContext, Context, UGetStandingsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetStandingsComplete, FBeamRequestContext, Context, UGetStandingsRequest*, Request);

using FGetStandingsFullResponse = FBeamFullResponse<UGetStandingsRequest*, UGetStandingsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetStandingsFullResponse, FGetStandingsFullResponse);
