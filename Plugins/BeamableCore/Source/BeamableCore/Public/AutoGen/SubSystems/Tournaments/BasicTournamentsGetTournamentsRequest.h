
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/TournamentQueryResponse.h"

#include "BasicTournamentsGetTournamentsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicTournamentsGetTournamentsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Running")
	FOptionalBool bIsRunning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id")
	FOptionalString ContentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cycle")
	FOptionalInt32 Cycle;

	// Body Params
	

	// Beam Base Request Declaration
	UBasicTournamentsGetTournamentsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_bIsRunning,_ContentId,_Cycle,Outer"))
	static UBasicTournamentsGetTournamentsRequest* MakeBasicTournamentsGetTournamentsRequest(FOptionalBool _bIsRunning, FOptionalString _ContentId, FOptionalInt32 _Cycle, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicTournamentsGetTournamentsSuccess, FBeamRequestContext, Context, UBasicTournamentsGetTournamentsRequest*, Request, UTournamentQueryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicTournamentsGetTournamentsError, FBeamRequestContext, Context, UBasicTournamentsGetTournamentsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicTournamentsGetTournamentsComplete, FBeamRequestContext, Context, UBasicTournamentsGetTournamentsRequest*, Request);

using FBasicTournamentsGetTournamentsFullResponse = FBeamFullResponse<UBasicTournamentsGetTournamentsRequest*, UTournamentQueryResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicTournamentsGetTournamentsFullResponse, FBasicTournamentsGetTournamentsFullResponse);
