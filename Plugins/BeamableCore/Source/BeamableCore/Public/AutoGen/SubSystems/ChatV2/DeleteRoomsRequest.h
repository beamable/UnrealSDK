
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/LeaveRoomRequestBody.h"
#include "AutoGen/LeaveRoomResponse.h"

#include "DeleteRoomsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteRoomsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	ULeaveRoomRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteRoomsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteRoomsRequest* MakeDeleteRoomsRequest(int64 _ObjectId, FString _RoomId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteRoomsSuccess, FBeamRequestContext, Context, UDeleteRoomsRequest*, Request, ULeaveRoomResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteRoomsError, FBeamRequestContext, Context, UDeleteRoomsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteRoomsComplete, FBeamRequestContext, Context, UDeleteRoomsRequest*, Request);

using FDeleteRoomsFullResponse = FBeamFullResponse<UDeleteRoomsRequest*, ULeaveRoomResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteRoomsFullResponse, FDeleteRoomsFullResponse);
