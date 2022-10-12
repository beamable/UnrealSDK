
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/GetStandingsResponse.h"

#include "GetStandingsGroupRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStandingsGroupRequest : public UObject, public IBeamBaseRequestInterface
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
	UGetStandingsGroupRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Max,_Focus,_Cycle,_From,Outer"))
	static UGetStandingsGroupRequest* MakeGetStandingsGroupRequest(FString _TournamentId, FOptionalInt32 _Max, FOptionalInt64 _Focus, FOptionalInt32 _Cycle, FOptionalInt32 _From, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStandingsGroupSuccess, FBeamRequestContext, Context, UGetStandingsGroupRequest*, Request, UGetStandingsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStandingsGroupError, FBeamRequestContext, Context, UGetStandingsGroupRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetStandingsGroupComplete, FBeamRequestContext, Context, UGetStandingsGroupRequest*, Request);

using FGetStandingsGroupFullResponse = FBeamFullResponse<UGetStandingsGroupRequest*, UGetStandingsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetStandingsGroupFullResponse, FGetStandingsGroupFullResponse);
