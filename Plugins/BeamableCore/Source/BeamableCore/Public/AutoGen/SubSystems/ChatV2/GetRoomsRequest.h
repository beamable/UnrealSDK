
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GetRoomsResponse.h"

#include "GetRoomsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRoomsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetRoomsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetRoomsRequest* MakeGetRoomsRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRoomsSuccess, FBeamRequestContext, Context, UGetRoomsRequest*, Request, UGetRoomsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRoomsError, FBeamRequestContext, Context, UGetRoomsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRoomsComplete, FBeamRequestContext, Context, UGetRoomsRequest*, Request);

using FGetRoomsFullResponse = FBeamFullResponse<UGetRoomsRequest*, UGetRoomsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetRoomsFullResponse, FGetRoomsFullResponse);
